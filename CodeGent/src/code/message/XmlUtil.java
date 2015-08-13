/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
<?xml version="1.0" encoding="UTF-8"?>
<messages>
<message name="ResPlayerInfo" type="SC">
    <field type="int"> id </field>
    <field type="string">name</field>
    <list type="vector">equip</list>
</message>
</messages>
 */

/**
 *
 * @author Administrator
 */
public class XmlUtil {
    public static ClzzInfo ReadClassFields(Element root){
        if( root != null ){
            ClzzInfo info = new ClzzInfo();
            info.setClazzName(root.attributeValue("name"));
            List<Element> elements = new ArrayList<Element>();
            elements.addAll(root.elements("field"));
            elements.addAll(root.elements("list"));
            for(Element ele :elements){
                ClassField field = new ClassField();
                field.setType(ele.attributeValue("type"));
                field.setName(ele.getStringValue());
                info.AddField(field);
            }
            return info;
        }
        return null;
    }
    
    public static List<ClzzInfo> ReadClazzInfo(String filepath){
        List<ClzzInfo> clazzs = new ArrayList<ClzzInfo>();
        try {
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(filepath));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> elements = root.elements("message");
            for(Element ele : elements){
                clazzs.add(ReadClassFields(ele));
            }
        } catch (DocumentException ex) {
            Logger.getLogger(XmlUtil.class.getName()).log(Level.SEVERE, null, ex);
        }
        return clazzs;
    }
}
