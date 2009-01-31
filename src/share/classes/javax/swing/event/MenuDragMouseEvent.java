/*
 * Copyright 1998-2006 Sun Microsystems, Inc.  All Rights Reserved.
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
package javax.swing.event;

import javax.swing.MenuElement;
import javax.swing.MenuSelectionManager;
import java.util.EventObject;
import java.awt.event.MouseEvent;
import java.awt.Component;


/**
 * MenuDragMouseEvent is used to notify interested parties that
 * the menu element has received a MouseEvent forwarded to it
 * under drag conditions.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @version %I% %G%
 * @author Georges Saab
 */
public class MenuDragMouseEvent extends MouseEvent {
    private MenuElement path[];
    private MenuSelectionManager manager;

    /**
     * Constructs a MenuDragMouseEvent object.
     * <p>Absolute coordinates xAbs and yAbs are set to source's location on screen plus
     * relative coordinates x and y. xAbs and yAbs are set to zero if the source is not showing.
     *
     * @param source        the Component that originated the event
     *                      (typically <code>this</code>)
     * @param id            an int specifying the type of event, as defined
     *                      in {@link java.awt.event.MouseEvent}
     * @param when          a long identifying the time the event occurred
     * @param modifiers     an int specifying any modifier keys held down,
     *                      as specified in {@link java.awt.event.InputEvent}
     * @param x             an int specifying the horizontal position at which
     *                      the event occurred, in pixels
     * @param y             an int specifying the vertical position at which
     *                      the event occurred, in pixels
     * @param clickCount    an int specifying the number of mouse-clicks
     * @param popupTrigger  a boolean -- true if the event {should?/did?}
     *                      trigger a popup
     * @param p             an array of MenuElement objects specifying a path
     *                        to a menu item affected by the drag
     * @param m             a MenuSelectionManager object that handles selections
     * @see MouseEvent#MouseEvent(java.awt.Component, int, long, int, int, int, int, int, int, boolean, int)
     */
    public MenuDragMouseEvent(Component source, int id, long when,
			      int modifiers, int x, int y, int clickCount,
			      boolean popupTrigger, MenuElement p[],
			      MenuSelectionManager m) {
        super(source, id, when, modifiers, x, y, clickCount, popupTrigger);
  	path = p;
  	manager = m;
    }

    /**
     * Constructs a MenuDragMouseEvent object.
     * <p>Even if inconsistent values for relative and absolute coordinates are
     * passed to the constructor, the MenuDragMouseEvent instance is still
     * created.
     * @param source        the Component that originated the event
     *                      (typically <code>this</code>)
     * @param id            an int specifying the type of event, as defined
     *                      in {@link java.awt.event.MouseEvent}
     * @param when          a long identifying the time the event occurred
     * @param modifiers     an int specifying any modifier keys held down,
     *                      as specified in {@link java.awt.event.InputEvent}
     * @param x             an int specifying the horizontal position at which
     *                      the event occurred, in pixels
     * @param y             an int specifying the vertical position at which
     *                      the event occurred, in pixels
     * @param xAbs          an int specifying the horizontal absolute position at which
     *                      the event occurred, in pixels
     * @param yAbs          an int specifying the vertical absolute position at which
     *                      the event occurred, in pixels
     * @param clickCount    an int specifying the number of mouse-clicks
     * @param popupTrigger  a boolean -- true if the event {should?/did?}
     *                      trigger a popup
     * @param p             an array of MenuElement objects specifying a path
     *                        to a menu item affected by the drag
     * @param m             a MenuSelectionManager object that handles selections
     * @see MouseEvent#MouseEvent(java.awt.Component, int, long, int, int, int, int, int, int, boolean, int)
     * @since 1.6
     */
    public MenuDragMouseEvent(Component source, int id, long when,
			      int modifiers, int x, int y, int xAbs,
                              int yAbs, int clickCount,
			      boolean popupTrigger, MenuElement p[],
			      MenuSelectionManager m) {
        super(source, id, when, modifiers, x, y, xAbs, yAbs, clickCount,
              popupTrigger, MouseEvent.NOBUTTON);
	path = p;
	manager = m;
    }

    /**
     * Returns the path to the selected menu item.
     *
     * @return an array of MenuElement objects representing the path value
     */
    public MenuElement[] getPath() {
	return path;
    }

    /**
     * Returns the current menu selection manager.
     *
     * @return a MenuSelectionManager object
     */
    public MenuSelectionManager getMenuSelectionManager() {
	return manager;
    }
}

