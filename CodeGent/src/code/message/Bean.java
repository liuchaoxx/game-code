/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import code.gent.ICodeGent;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import org.dom4j.Element;

/**
 *
 * @author Administrator
 */
public class Bean implements ICodeGent{
    private String name;
    private String describe;
    private List<ClassField> cfields = new ArrayList<ClassField>();

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescribe() {
        return describe;
    }

    public void setDescribe(String describe) {
        this.describe = describe;
    }

    public void AddField(ClassField field) {
        cfields.add(field);
    }

    public List<ClassField> getField() {
        return cfields;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Message) {
            return this.name.equals(((Bean) obj).name);
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 29 * hash + Objects.hashCode(this.name);
        return hash;
    }

    public boolean readXml(Element ele) {
        this.name = ele.attributeValue("name");
        this.describe = ele.attributeValue("desc");
        List<Element> elements = new ArrayList<Element>();
        elements.addAll(ele.elements("field"));
        elements.addAll(ele.elements("list"));
        for (Element element : elements) {
            ClassField field = new ClassField();
            if (!field.read(element))
                return false;
            cfields.add(field);
        }
        return (null != this.name && !"".equals(name)
                && null != this.describe && !"".equals(describe));
    }
    
    @Override
    public Map buildMap(){
        Map<String, Object> map = new HashMap<String, Object>();
        map.put("name", name);
        map.put("describe", describe);
        map.put("fields", cfields);
        return map;
    }
}
