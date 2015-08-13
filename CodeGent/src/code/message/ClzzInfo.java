/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import java.util.ArrayList;
import java.util.List;

public class ClzzInfo {
    private String clazzName;
    private List<ClassField> cfields = new ArrayList<ClassField>();

    public String getClazzName() {
        return clazzName;
    }

    public void setClazzName(String clazzName) {
        this.clazzName = clazzName;
    }
    
    public void AddField(ClassField field){
        cfields.add(field);
    }
    public List<ClassField> getField(){
        return cfields;
    }
}
