/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import java.util.Objects;
import org.dom4j.Element;

/**
 *
 * @author Administrator
 */
public class ClassField {
    private String ptype;
    private String name;
    private String ftype;
    private String describe;

    public String getPtype() {
        return ptype;
    }

    public void setPtype(String ptype) {
        this.ptype = ptype;
    }

    public String getFtype() {
        return ftype;
    }

    public void setFtype(String ftype) {
        this.ftype = ftype;
    }

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
    
    @Override
    public boolean equals(Object obj){
        if(obj instanceof ClassField){
            return this.name.equals(((ClassField)obj).name);
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 79 * hash + Objects.hashCode(this.name);
        return hash;
    }
    
    public boolean read(Element ele){
        this.ptype = ele.attributeValue("type");
        this.describe = ele.attributeValue("desc");
        this.ftype = ele.getNodeTypeName();
        this.name = ele.getStringValue();
        return (null != this.name && !"".equals(name) 
                && null != this.ptype && !"".equals(ptype) && null != this.describe && !"".equals(describe));
    }
}
