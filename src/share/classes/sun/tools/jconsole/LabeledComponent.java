/*
 * Copyright 2004-2006 Sun Microsystems, Inc.  All Rights Reserved.
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

package sun.tools.jconsole;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

@SuppressWarnings("serial")
public class LabeledComponent extends JPanel {
    JPanel rightPanel;
    String labelStr, valueLabelStr, compoundStr;
    JLabel label;
    JComponent comp;

    public LabeledComponent(String text, JComponent comp) {
	this(text, 0, comp);
    }

    public LabeledComponent(String text, int mnemonic, JComponent comp) {
	super(new BorderLayout(6, 6));

	this.labelStr = text;
	this.label = new JLabel(text, JLabel.RIGHT);
	this.comp = comp;

	label.setLabelFor(comp);
	if (mnemonic > 0) {
	    label.setDisplayedMnemonic(mnemonic);
	}

	add(label, BorderLayout.WEST);
	add(comp,  BorderLayout.CENTER);
    }

    public void setLabel(String str) {
	this.labelStr = str;
	updateLabel();
    }

    public void setValueLabel(String str) {
	this.valueLabelStr = str;
	updateLabel();
    }

    private void updateLabel() {
	String str = labelStr;
	label.setText(str);
	this.compoundStr = str; 
	JComponent container = (JComponent)getParent();
	LabeledComponent.layout(container);
    }

    public static void layout(Container container) {
	int wMax = 0;

	for (Component c : container.getComponents()) {
	    if (c instanceof LabeledComponent) {
		LabeledComponent lc = (LabeledComponent)c;
lc.label.setPreferredSize(null);
//		int w = lc.label.getMinimumSize().width;
int w = lc.label.getPreferredSize().width;
		if (w > wMax) {
		    wMax = w;
		}
	    }
	}

	for (Component c : container.getComponents()) {
	    if (c instanceof LabeledComponent) {
		LabeledComponent lc = (LabeledComponent)c;
		JLabel label = lc.label;
		int h = label.getPreferredSize().height;

		label.setPreferredSize(new Dimension(wMax, h));
		label.setHorizontalAlignment(JLabel.RIGHT);
	    }
	}
    }
}
