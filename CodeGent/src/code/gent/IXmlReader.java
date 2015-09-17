/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.gent;

import org.dom4j.Element;

/**
 *
 * @author Administrator
 */
public interface IXmlReader {
    public abstract boolean readXml(Element elem);
}
