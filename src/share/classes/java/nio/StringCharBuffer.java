/*
 * Copyright 2000-2005 Sun Microsystems, Inc.  All Rights Reserved.
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

package java.nio;


// ## If the sequence is a string, use reflection to share its array

class StringCharBuffer					// package-private
    extends CharBuffer
{
    CharSequence str;

    StringCharBuffer(CharSequence s, int start, int end) { // package-private
	super(-1, start, end, s.length());
	int n = s.length();
	if ((start < 0) || (start > n) || (end < start) || (end > n))
	    throw new IndexOutOfBoundsException();
	str = s;
    }

    public CharBuffer slice() {
	return new StringCharBuffer(str,
				    -1,
				    0, 
				    this.remaining(),
				    this.remaining(),
				    this.position());
    }

    private StringCharBuffer(CharSequence s,
			     int mark,
			     int pos,
			     int limit,
			     int cap,
			     int offset) {
	super(mark, pos, limit, cap, null, offset);
	str = s;
    }

    private StringCharBuffer(CharSequence s, int mark,
			     int pos, int limit, int cap)
    {
	super(mark, pos, limit, cap);
	str = s;
    }

    public CharBuffer duplicate() {
	return new StringCharBuffer(str, markValue(),
				    position(), limit(), capacity());
    }

    public CharBuffer asReadOnlyBuffer() {
	return duplicate();
    }

    public final char get() {
	return str.charAt(nextGetIndex());
    }

    public final char get(int index) {
	return str.charAt(checkIndex(index));
    }

    // ## Override bulk get methods for better performance

    public final CharBuffer put(char c) {
	throw new ReadOnlyBufferException();
    }

    public final CharBuffer put(int index, char c) {
	throw new ReadOnlyBufferException();
    }

    public final CharBuffer compact() {
	throw new ReadOnlyBufferException();
    }

    public final boolean isReadOnly() {
	return true;
    }

    final String toString(int start, int end) {
	return str.toString().substring(start, end);
    }

    public final CharSequence subSequence(int start, int end) {
	try {
	    int pos = position();
	    return new StringCharBuffer(str,
					pos + checkIndex(start, pos),
					pos + checkIndex(end, pos));
	} catch (IllegalArgumentException x) {
	    throw new IndexOutOfBoundsException();
	}
    }

    public boolean isDirect() {
	return false;
    }

    public ByteOrder order() {
	return ByteOrder.nativeOrder();
    }

}
