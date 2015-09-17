/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import code.gent.IXmlReader;
import org.dom4j.Element;

public class Message extends Bean implements IXmlReader{
    private String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
    
    @Override
   public boolean readXml(Element ele){
       this.type = ele.attributeValue("type");
       return super.readXml(ele);
   }
}
