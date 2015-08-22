/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.set;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import net.sf.json.JSONObject;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 *
 * @author Administrator
 */
public class SetManager {

    private static SetManager manager = null;
    private Map<String, Object> setmap = new HashMap<String, Object>();

    private SetManager() {
        load_path_config();
    }

    public static SetManager getInstance() {
        if (manager == null) {
            manager = new SetManager();
        }
        return manager;
    }

    private void load_path_config() {
        try {
            String filepath ="../config/config.xml";
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(filepath));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> pelements = root.elements("paths");
            for (Element pele : pelements) {
                List<Element> elements = pele.elements();
                for (Element ele : elements) {
                    setmap.put(ele.getName(), ele.getStringValue());
                }
            }
        } catch (DocumentException ex) {
        }
    }

    public Object get(String type){
        return setmap.containsKey(type) ? setmap.get(type):null;
    }
}
