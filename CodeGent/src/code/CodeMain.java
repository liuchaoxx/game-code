package code;

import code.message.ClazzManager;
import code.set.SetManager;
import code.set.SetType;
import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

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
        if (args[0].equals("-msg")) {
            JOptionPane.showMessageDialog( null , generator_msg_file() ,"生成结果" , JOptionPane.ERROR_MESSAGE);     
        }else if (args[0].equals("-sql")) {
            JOptionPane.showMessageDialog( null , generatoe_sql_bean() ,"生成结果" , JOptionPane.ERROR_MESSAGE);     
        }
        
    }

    public static String generator_msg_file() {
        String xmlpath = (String) SetManager.getInstance().get(SetType.MESSAGE_XML_PATH);
        if (xmlpath == null || "".equals(xmlpath)) {
            return "消息xml路径错误";
        }
        JFileChooser filechooser = new JFileChooser();//创建文件选择器
        filechooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        filechooser.setCurrentDirectory(new File(xmlpath));//设置当前目录
        filechooser.setAcceptAllFileFilterUsed(false);
        filechooser.showDialog(new JLabel(), "选择");
        //显示所有文件
        filechooser.addChoosableFileFilter(new FileNameExtensionFilter("XML Files", "xml"));
        File selectedFile = filechooser.getSelectedFile();
        if (selectedFile == null) {
            return "请选择正确的xml文件";
        }
        String savepath = (String) SetManager.getInstance().get(SetType.MESSAGE_SAVE_PATH);
        if (savepath == null || "".equals(savepath)) {
             return "保存路径错误";
        }
        return ClazzManager.getInstance().generator(savepath, selectedFile.getName(), "message.ftl");
    }
    
    public static String generatoe_sql_bean(){
        return null;
    }
    
}
