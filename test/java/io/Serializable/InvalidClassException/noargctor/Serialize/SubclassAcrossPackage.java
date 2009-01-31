/* 
 * Copyright 1998 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
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

/*
 * @bug 4093279
 * REMOVED test, build and run tag since could not get this to work.
 * Test is run via shell script, run.sh.
 */

package Serialize;

import java.io.*;

class PublicSerializable
extends NonSerializable.PublicCtor implements Serializable
{
    int field1 = 5;
};

class ProtectedSerializable
extends NonSerializable.ProtectedCtor implements Serializable
{
    int field1 = 5;
};

class DifferentPackageSerializable
extends NonSerializable.PackageCtor implements Serializable
{
    int field1 = 5;
    DifferentPackageSerializable() {
	super(1);
    }
};

class SamePackageSerializable
extends Serialize.SamePackageCtor implements Serializable
{
    SamePackageSerializable() {
    }
};

class SamePackageProtectedCtor {
    protected SamePackageProtectedCtor() {
    }
};

class SamePackageProtectedSerializable
extends Serialize.SamePackageProtectedCtor implements Serializable
{
    SamePackageProtectedSerializable() {
    }
};


class SamePackagePrivateCtor {
    private SamePackagePrivateCtor() {
    }
    public SamePackagePrivateCtor(int l) {
    }
};

class SamePackagePrivateSerializable
extends Serialize.SamePackagePrivateCtor implements Serializable
{
    SamePackagePrivateSerializable() {
	super(1);
    }
};

class PrivateSerializable
extends NonSerializable.PrivateCtor implements Serializable
{
    int field1 = 5;

    PrivateSerializable() {
	super(1);
    }
};

class ExternalizablePublicCtor implements Externalizable {
    public ExternalizablePublicCtor() {
    }
    public void writeExternal(ObjectOutput out) throws IOException {
    }
    public void readExternal(ObjectInput in)
	throws IOException, ClassNotFoundException
	{
	} 
};

class ExternalizableProtectedCtor implements Externalizable {
    protected ExternalizableProtectedCtor() {
    }
    public void writeExternal(ObjectOutput out) throws IOException {
    }
    public void readExternal(ObjectInput in)
	throws IOException, ClassNotFoundException
	{
	} 
};

class ExternalizablePackageCtor implements Externalizable {
    ExternalizablePackageCtor() {
    }
    public void writeExternal(ObjectOutput out) throws IOException {
    }
    public void readExternal(ObjectInput in)
	throws IOException, ClassNotFoundException
	{
	} 
};

class ExternalizablePrivateCtor implements Externalizable {
    private ExternalizablePrivateCtor() {
    }
    public ExternalizablePrivateCtor(int i) {
    }
    public void writeExternal(ObjectOutput out) throws IOException {
    }
    public void readExternal(ObjectInput in)
	throws IOException, ClassNotFoundException
	{
	} 
};


public class SubclassAcrossPackage {
    public static void main(String args[])
	throws IOException, ClassNotFoundException
	{
	    ByteArrayOutputStream baos = new ByteArrayOutputStream();
	    ObjectOutputStream out =   new ObjectOutputStream(baos);
	    out.writeObject(new PublicSerializable());
	    out.writeObject(new ProtectedSerializable());
	    out.writeObject(new SamePackageSerializable());
	    out.writeObject(new SamePackageProtectedSerializable());
	    out.writeObject(new DifferentPackageSerializable());
	
	    InputStream is = new ByteArrayInputStream(baos.toByteArray());
	    ObjectInputStream in = new ObjectInputStream(is);
	    /* (PublicSerializable)*/ in.readObject();
	    /* (ProtectedSerializable) */ in.readObject();
	    /* (SamePackageSerializable) */ in.readObject();	 
	    /* (SamePackageProtectedSerializable) */ in.readObject();
	    try {
	    /* (DifferentPackageSerializable) */ in.readObject();
	    } catch (InvalidClassException e) {
	    }
	    in.close();

	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new PrivateSerializable());
	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    try {
		/* (PrivateSerializable) */ in.readObject();
		throw new Error("Expected InvalidClassException reading PrivateSerialziable");
	    } catch (InvalidClassException e) {
	    } 
	    in.close();

	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new SamePackagePrivateSerializable());
	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    try {
		/* (SamePackagePrivateSerializable) */ in.readObject();
		throw new Error("Expected InvalidClassException reading PrivateSerialziable");
	    } catch (InvalidClassException e) {
	    } 
	    in.close();

	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new ExternalizablePublicCtor());

	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    /* (ExternalizablePublicCtor) */ in.readObject();
	    in.close();

	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new ExternalizableProtectedCtor());
	

	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    try {
		/* (ExternalizableProtectedCtor) */ in.readObject();
		throw new Error("Expected InvalidClassException reading ExternalizableProtectedCtor");
	    } catch (InvalidClassException e) {
	    }
	    in.close();

	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new ExternalizablePackageCtor());

	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    try {
		/* (ExternalizablePackageCtor) */ in.readObject();
		throw new Error("Expected InvalidClassException reading ExternalizablePackageCtor");
	    } catch (InvalidClassException e) {
	    }
	    in.close();
      
	    baos.reset();
	    out = new ObjectOutputStream(baos);
	    out.writeObject(new ExternalizablePrivateCtor(2));

	    in = new ObjectInputStream(new ByteArrayInputStream(baos.toByteArray()));
	    try {
		/* (ExternalizablePrivateCtor) */ in.readObject();
		throw new Error("Expected InvalidClassException reading ExternalizablePrivateCtor");
	    } catch (InvalidClassException e) {
	    }
	    out.close();
	    in.close();
	}
}

