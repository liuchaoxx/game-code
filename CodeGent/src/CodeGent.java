/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import code.message.ClzzInfo;
import code.message.XmlUtil;
import java.util.List;

/**
 *
 * @author Administrator
 */
public class CodeGent {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        String path = "E:\\workspace\\game-code\\message.xml";
        List<ClzzInfo> infos = XmlUtil.ReadClazzInfo(path);
        System.out.println("info size == "+ infos.size() );
    }
    
}
