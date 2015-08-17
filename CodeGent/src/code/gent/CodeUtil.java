/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.gent;

import freemarker.template.Configuration;
import freemarker.template.Template;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class CodeUtil {
    private static Configuration config = null;
    
    public CodeUtil(String ftlpath){
        try {
            config = new Configuration();
            config.setDirectoryForTemplateLoading(new File(ftlpath));
        } catch (IOException ex) {
            ex.printStackTrace();    
        }
    }
    
     /** 
     * 生成代码文件 
     * @param root
     * @param ftltemp
     * @param savepath
     * @param filename
     */  
    public void buildFile(Map root, String ftltemp, String savepath, String filename)   
    {    
        try {    
            Template template       = config.getTemplate("ftltemp");   
            File newsDir = new File(savepath);    
            if (!newsDir.exists()) {    
                newsDir.mkdirs();    
            }   
            Writer out = new OutputStreamWriter(  
                        new FileOutputStream(savepath + filename),  
                        "UTF-8");  
            template.process(root, out);    
        } catch (Exception e) {    
            e.printStackTrace();    
        }    
    }    
}
