/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.message;

import code.gent.CodeUtil;
import code.set.SetManager;
import code.set.SetType;
import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

public final class ClazzManager {

    private static ClazzManager manager = null;
    private Set<String> beans_name = new HashSet<String>();
    private Set<String> field_type = new HashSet<String>();
    private Set<String> class_type = new HashSet<String>();

    public static ClazzManager getInstance() {
        if (manager == null) {
            manager = new ClazzManager();
        }
        return manager;
    }

    private ClazzManager() {
        try {
            String msg_path = (String) SetManager.getInstance().get(SetType.MESSAGE_XML_PATH);
            if (msg_path != null && !"".equals(msg_path)) {
                readClassType("../config/main.xml");
                readFieldType("../config/main.xml");
                readBeans(msg_path);
            }
        } catch (DocumentException ex) {
            Logger.getLogger(ClazzManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private boolean readBeans(String path) throws DocumentException {
        File filedic = new File(path);
        if (null == filedic) {
            return false;
        }

        if (!filedic.isDirectory()) {
            return false;
        }

        File[] files = filedic.listFiles();
        if (null == files || files.length == 0) {
            return false;
        }

        SAXReader saxReader = new SAXReader();
        for (int i = 0; i < files.length; i++) {
            File file = files[i];
            if (!file.getName().endsWith(".xml")) {
                continue;
            }

            Document document = saxReader.read(file);
            if (null == document) {
                return false;
            }
            Element root = document.getRootElement();
            List<Element> elements = root.elements("bean");
            for (Element ele : elements) {
                String name = ele.attributeValue("name");
                if (null == name || "".equals(name)) {
                    return false;
                }
                if (beans_name.contains(name)) {
                    return false;
                }
                beans_name.add(name);
            }
        }
        return true;
    }

    private void readFieldType(String filepath) {
        try {
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(filepath));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> pelements = root.elements("ftypes");
            for (Element pele : pelements) {
                List<Element> elements = pele.elements("ftype");
                for (Element ele : elements) {
                    field_type.add(ele.getStringValue());
                }
            }
        } catch (DocumentException ex) {
            Logger.getLogger(ClazzManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void readClassType(String filepath) {
        try {
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(filepath));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> pelements = root.elements("ctypes");
            for (Element pele : pelements) {
                List<Element> elements = pele.elements("ctype");
                for (Element ele : elements) {
                    class_type.add(ele.getStringValue());
                }
            }
        } catch (DocumentException ex) {
            Logger.getLogger(ClazzManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public List<ClazzInfo> readClazzInfo(String filepath) {
        List<ClazzInfo> clazzs = new ArrayList<ClazzInfo>();
        try {
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(filepath));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> elements = root.elements("message");
            for (Element ele : elements) {
                ClazzInfo info = new ClazzInfo();
                if (!info.read(ele)) {
                    return null;
                }
                clazzs.add(info);
            }
        } catch (DocumentException ex) {
            Logger.getLogger(ClazzManager.class.getName()).log(Level.SEVERE, null, ex);
        }
        return clazzs;
    }

    public List<BeanInfo> readBeanList(String path) {
        List<BeanInfo> beans = new ArrayList<BeanInfo>();
        try {
            SAXReader saxReader = new SAXReader();
            Document document = saxReader.read(new File(path));
            Element root = document.getRootElement(); // 获取根元素
            List<Element> elements = root.elements("bean");
            for (Element ele : elements) {
                BeanInfo info = new BeanInfo();
                if (!info.read(ele)) {
                    return null;
                }
                beans.add(info);
            }
        } catch (DocumentException ex) {
            Logger.getLogger(ClazzManager.class.getName()).log(Level.SEVERE, null, ex);
        }
        return beans;
    }

    public boolean checkBeeanFileList(BeanInfo info) {
        List<ClassField> fields = info.getField();
        for (ClassField field : fields) {
            if (field.getFtype().equals("field")) {
                if (!field_type.contains(field.getPtype())) {
                    return false;
                }
                field.setCtype("base");
            } else if (field.getFtype().equals("list")) {
                if (field_type.contains(field.getPtype())) {
                    field.setCtype("base");
                } else if (beans_name.contains(field.getPtype())) {
                    field.setCtype("class");
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    public boolean checkClazzFieldList(ClazzInfo info) {
        if (!class_type.contains(info.getType())) {
            return false;
        }
        return checkBeeanFileList(info);
    }

    public String generator(String path, String filename, String template) {
        String msg_path = (String) SetManager.getInstance().get(SetType.MESSAGE_XML_PATH);
        if (msg_path == null || "".equals(msg_path)) {
            return "xml路径错误";
        }
        CodeUtil util = new CodeUtil(System.getProperty("user.dir") + "\\ftl\\");
        List<BeanInfo> readBeanList = readBeanList(msg_path + filename);
        for (BeanInfo bean : readBeanList) {
            if (!checkBeeanFileList(bean)) {
                return bean.getName()+"格式错误";
            }
            util.buildFile(bean.buildMap(), template, path, bean.getName());
        }
        return "生成成功";
    }
}
