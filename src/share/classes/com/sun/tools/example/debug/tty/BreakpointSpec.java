/*
 * Copyright 1998-2003 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */

package com.sun.tools.example.debug.tty;

import com.sun.jdi.*;
import com.sun.jdi.request.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

class BreakpointSpec extends EventRequestSpec {
    String methodId;
    List methodArgs;
    int lineNumber;

    BreakpointSpec(ReferenceTypeSpec refSpec, int lineNumber) {
        super(refSpec);
        this.methodId = null;
        this.methodArgs = null;
        this.lineNumber = lineNumber;
    }

    BreakpointSpec(ReferenceTypeSpec refSpec, String methodId, 
                   List methodArgs) throws MalformedMemberNameException {
        super(refSpec);
        this.methodId = methodId;
        this.methodArgs = methodArgs;
        this.lineNumber = 0;
        if (!isValidMethodName(methodId)) {
            throw new MalformedMemberNameException(methodId);
        }
    }

    /**
     * The 'refType' is known to match, return the EventRequest.
     */
    EventRequest resolveEventRequest(ReferenceType refType) 
                           throws AmbiguousMethodException,
                                  AbsentInformationException,
                                  InvalidTypeException,
                                  NoSuchMethodException,
                                  LineNotFoundException {
        Location location = location(refType);
	if (location == null) {
	    throw new InvalidTypeException();
	}
        EventRequestManager em = refType.virtualMachine().eventRequestManager();
        EventRequest bp = em.createBreakpointRequest(location);
        bp.setSuspendPolicy(suspendPolicy);
        bp.enable();
        return bp;
    }

    String methodName() {
        return methodId;
    }

    int lineNumber() {
        return lineNumber;
    }

    List methodArgs() {
        return methodArgs;
    }

    boolean isMethodBreakpoint() {
        return (methodId != null);
    }

    public int hashCode() {
        return refSpec.hashCode() + lineNumber + 
            ((methodId != null) ? methodId.hashCode() : 0) +
            ((methodArgs != null) ? methodArgs.hashCode() : 0);
    }

    public boolean equals(Object obj) {
        if (obj instanceof BreakpointSpec) {
            BreakpointSpec breakpoint = (BreakpointSpec)obj;

            return ((methodId != null) ? 
                        methodId.equals(breakpoint.methodId) 
                      : methodId == breakpoint.methodId) &&
                   ((methodArgs != null) ? 
                        methodArgs.equals(breakpoint.methodArgs)
                      : methodArgs == breakpoint.methodArgs) &&
                   refSpec.equals(breakpoint.refSpec) &&
                   (lineNumber == breakpoint.lineNumber);
        } else {
            return false;
        }
    }

    String errorMessageFor(Exception e) { 
        if (e instanceof AmbiguousMethodException) {
            return (MessageOutput.format("Method is overloaded; specify arguments",
                                         methodName()));
            /*
             * TO DO: list the methods here
             */
        } else if (e instanceof NoSuchMethodException) {
            return (MessageOutput.format("No method in",
                                         new Object [] {methodName(),
                                                        refSpec.toString()}));
        } else if (e instanceof AbsentInformationException) {
            return (MessageOutput.format("No linenumber information for",
                                         refSpec.toString()));
        } else if (e instanceof LineNotFoundException) {
            return (MessageOutput.format("No code at line",
                                         new Object [] {new Long (lineNumber()),
                                                        refSpec.toString()}));
        } else if (e instanceof InvalidTypeException) {
            return (MessageOutput.format("Breakpoints can be located only in classes.",
                                         refSpec.toString()));
        } else {
            return super.errorMessageFor( e);
        } 
    }

    public String toString() {
        StringBuffer buffer = new StringBuffer(refSpec.toString());
        if (isMethodBreakpoint()) {
            buffer.append('.');
            buffer.append(methodId);
            if (methodArgs != null) {
                Iterator iter = methodArgs.iterator();
                boolean first = true;
                buffer.append('(');
                while (iter.hasNext()) {
                    if (!first) {
                        buffer.append(',');
                    }
                    buffer.append((String)iter.next());
                    first = false;
                }
                buffer.append(")");
            }
        } else {
            buffer.append(':');
            buffer.append(lineNumber);
        }
        return MessageOutput.format("breakpoint", buffer.toString());
    }

    private Location location(ReferenceType refType) throws 
                                    AmbiguousMethodException,
                                    AbsentInformationException,
                                    NoSuchMethodException,
                                    LineNotFoundException {
        Location location = null;
        if (isMethodBreakpoint()) {
            Method method = findMatchingMethod(refType);
            location = method.location();
        } else {
            // let AbsentInformationException be thrown
            List locs = refType.locationsOfLine(lineNumber());
            if (locs.size() == 0) {
                throw new LineNotFoundException();
            }
            // TO DO: handle multiple locations
            location = (Location)locs.get(0);
            if (location.method() == null) {
                throw new LineNotFoundException();
            } 
        }
        return location;
    }

    private boolean isValidMethodName(String s) {
        return isJavaIdentifier(s) || 
               s.equals("<init>") ||
               s.equals("<clinit>");
    }

    /* 
     * Compare a method's argument types with a Vector of type names.
     * Return true if each argument type has a name identical to the 
     * corresponding string in the vector (allowing for varars)
     * and if the number of arguments in the method matches the 
     * number of names passed
     */
    private boolean compareArgTypes(Method method, List nameList) {
        List argTypeNames = method.argumentTypeNames();

        // If argument counts differ, we can stop here
        if (argTypeNames.size() != nameList.size()) {
            return false;
        }

        // Compare each argument type's name
        int nTypes = argTypeNames.size();
        for (int i = 0; i < nTypes; ++i) {
            String comp1 = (String)argTypeNames.get(i);
            String comp2 = (String)nameList.get(i);
            if (! comp1.equals(comp2)) {
                /*
                 * We have to handle varargs.  EG, the
                 * method's last arg type is xxx[]
                 * while the nameList contains xxx...
                 * Note that the nameList can also contain
                 * xxx[] in which case we don't get here.
                 */
                if (i != nTypes - 1 || 
                    !method.isVarArgs()  ||
                    !comp2.endsWith("...")) {
                    return false;
                }
                /*
                 * The last types differ, it is a varargs
                 * method and the nameList item is varargs.
                 * We just have to compare the type names, eg,
                 * make sure we don't have xxx[] for the method
                 * arg type and yyy... for the nameList item.
                 */
                int comp1Length = comp1.length();
                if (comp1Length + 1 != comp2.length()) {
                    // The type names are different lengths
                    return false;
                }
                // We know the two type names are the same length
                if (!comp1.regionMatches(0, comp2, 0, comp1Length - 2)) {
                    return false;
                }
                // We do have xxx[] and xxx... as the last param type
                return true;
            }
        }

        return true;
    }


    /*
     * Remove unneeded spaces and expand class names to fully 
     * qualified names, if necessary and possible.
     */
    private String normalizeArgTypeName(String name) {
        /* 
         * Separate the type name from any array modifiers, 
         * stripping whitespace after the name ends
         */
        int i = 0;
        StringBuffer typePart = new StringBuffer();
        StringBuffer arrayPart = new StringBuffer();
        name = name.trim();
        int nameLength = name.length();
        /*
         * For varargs, there can be spaces before the ... but not
         * within the ...  So, we will just ignore the ...
         * while stripping blanks.
         */
        boolean isVarArgs = name.endsWith("...");
        if (isVarArgs) {
            nameLength -= 3;
        }
        while (i < nameLength) {
            char c = name.charAt(i);
            if (Character.isWhitespace(c) || c == '[') {
                break;      // name is complete
            }
            typePart.append(c);
            i++;
        }
        while (i < nameLength) {
            char c = name.charAt(i);
            if ( (c == '[') || (c == ']')) {
                arrayPart.append(c);
            } else if (!Character.isWhitespace(c)) {
                throw new IllegalArgumentException
                    (MessageOutput.format("Invalid argument type name"));
            }
            i++;
        }
        name = typePart.toString();

        /*
         * When there's no sign of a package name already, try to expand the 
         * the name to a fully qualified class name
         */
        if ((name.indexOf('.') == -1) || name.startsWith("*.")) {
            try {
                ReferenceType argClass = Env.getReferenceTypeFromToken(name);
                if (argClass != null) {
                    name = argClass.name();
                }
            } catch (IllegalArgumentException e) {
                // We'll try the name as is 
            }
        }
        name += arrayPart.toString();
        if (isVarArgs) {
            name += "...";
        }
        return name;
    }

    /* 
     * Attempt an unambiguous match of the method name and 
     * argument specification to a method. If no arguments 
     * are specified, the method must not be overloaded.
     * Otherwise, the argument types much match exactly 
     */
    private Method findMatchingMethod(ReferenceType refType) 
                                        throws AmbiguousMethodException,
                                               NoSuchMethodException {

        // Normalize the argument string once before looping below.
        List<String> argTypeNames = null;
        if (methodArgs() != null) {
            argTypeNames = new ArrayList<String>(methodArgs().size());
            Iterator iter = methodArgs().iterator();
            while (iter.hasNext()) {
                String name = (String)iter.next();
                name = normalizeArgTypeName(name);
                argTypeNames.add(name);
            }
        }

        // Check each method in the class for matches
        Iterator iter = refType.methods().iterator();
        Method firstMatch = null;  // first method with matching name
        Method exactMatch = null;  // (only) method with same name & sig
        int matchCount = 0;        // > 1 implies overload
        while (iter.hasNext()) {
            Method candidate = (Method)iter.next();

            if (candidate.name().equals(methodName())) {
                matchCount++;

                // Remember the first match in case it is the only one
                if (matchCount == 1) {
                    firstMatch = candidate;
                }

                // If argument types were specified, check against candidate
                if ((argTypeNames != null) 
                        && compareArgTypes(candidate, argTypeNames) == true) {
                    exactMatch = candidate;
                    break;
                }
            }
        }

        // Determine method for breakpoint
        Method method = null;
        if (exactMatch != null) {
            // Name and signature match
            method = exactMatch;
        } else if ((argTypeNames == null) && (matchCount > 0)) {
            // At least one name matched and no arg types were specified
            if (matchCount == 1) {
                method = firstMatch;       // Only one match; safe to use it
            } else {
                throw new AmbiguousMethodException();
            }
        } else {
            throw new NoSuchMethodException(methodName());
        }
        return method;
    }
}
