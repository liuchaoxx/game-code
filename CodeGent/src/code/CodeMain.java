package code;

import code.message.ClazzManager;
import code.ui.GentSelectUI;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Administrator
 */
public class CodeMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       // ClazzManager.getInstance().generator("E:\\workspace\\game-code\\CodeGent\\ftl\\", "message.xml", "message.ftl");
        //实例化一个showCalculaterFrame类的对象 
        GentSelectUI ui = new GentSelectUI(); 
        //调用计算器界面的方法 
        ui.initGUI(); 
    }

}
