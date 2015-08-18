/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.ui;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import net.sf.json.JSONObject;

/**
 *
 * @author Administrator
 */
public class SetManager {

    private static SetManager manager = null;
    private Map<int, Object> setmap = new HashMap<int, Object>();

    private SetManager() {
        loadset();
    }

    public static SetManager getInstance() {
        if (manager == null) {
            manager = new SetManager();
        }
        return manager;
    }

    public void loadset() {
        String confpath = System.getProperty("user.dir")+ "\\config\\config.txt";
        File file = new File(confpath);
        assert (file == null);
        assert (file.isDirectory());
        String str = "";
        try {
            FileInputStream in = new FileInputStream(file);
            int size = in.available();
            byte[] buffer = new byte[size];
            in.read(buffer);
            in.close();
            str = new String(buffer, "GB2312");
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (str != null || !"".equals(str)) {
            JSONObject jsonObject = JSONObject.fromObject(str);
            Map<String, Object> map = (Map<String, Object>) JSONObject.toBean(jsonObject, Map.class);
            setmap.putAll(map);
        }
    }

    public void saveset() {
        JSONObject jsonObject = JSONObject.fromObject(setmap);
        String fileName = System.getProperty("user.dir")+ "\\config\\config.txt";
        try {
            //使用这个构造函数时，如果存在kuka.txt文件，
            //则先把这个文件给删除掉，然后创建新的kuka.txt
            FileWriter writer = new FileWriter(fileName);
            writer.write(jsonObject.toString());
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void set(int type, Object obj){
        if (obj != null) {
            setmap.put(type, obj);
        }
    }
    
    public static void main(String[] argv){
        
    }
}
