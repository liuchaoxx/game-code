/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import org.dom4j.Element;

public class ClazzInfo extends BeanInfo{
    private String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
    
   @Override
   public boolean read(Element ele){
       this.type = ele.attributeValue("type");
       return super.read(ele);
   }
}
