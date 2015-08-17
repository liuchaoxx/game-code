package code;

import code.message.ClazzManager;

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
        ClazzManager.getInstance().codeGenerator("E:\\workspace\\game-code\\CodeGent\\ftl\\", "message.xml");
    }

}
