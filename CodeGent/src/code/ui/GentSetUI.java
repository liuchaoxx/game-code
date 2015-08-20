/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.ui;

import code.set.SetManager;
import code.set.SetType;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

/**
 *
 * @author Administrator
 */
public class GentSetUI implements GentUI {

    @Override
    public void initGUI() {
        //实例化一个JFrame类的对象 
        javax.swing.JFrame jf = new javax.swing.JFrame();
        //设置窗体的标题属性 
        jf.setTitle("代码生成器");
        //设置窗体的大小属性 
        jf.setSize(500, 500);
        //设置窗体的位置属性 
        jf.setLocation(400, 200);
        //设置窗体关闭时退出程序 
        jf.setDefaultCloseOperation(3);
        //设置禁止调整窗体的大小 
        jf.setResizable(false);

        //javax.swing.JTextField jteName = new javax.swing.JTextField(20); 
        //将jteName添加到容器JFrame上 
        //jf.add(jteName); 
        //实例化一个布局类对象 
        //java.awt.GridLayout gr = new java.awt.GridLayout(3, 1);
        //设置窗体的布局方式为网格布局 
        jf.setLayout(null);
        JLabel jlabel = new JLabel("保存目录", SwingConstants.CENTER);
        jlabel.setSize(70, 30);
        jlabel.setLocation(10, 10);
        jf.add(jlabel);
        //实例化十九个个JButton对象、一个JTextField对象 
        final JTextField jfd1 = new JTextField();
        jfd1.setSize(250, 30);
        jfd1.setLocation(90, 10);
        String savepath = (String) SetManager.getInstance().get(SetType.MESSAGE_SAVE_PATH);
        if (savepath != null && !"".equals(savepath)) {
            jfd1.setText(savepath);
        }
        jf.add(jfd1);
        JButton jb1 = new JButton("浏览");
        jb1.setSize(70, 30);
        jb1.setLocation(350, 10);
        jf.add(jb1);
        //设置窗体是否可见 
        jf.setVisible(true);
        jb1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser jfc1 = new JFileChooser();
                jfc1.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                String savepath = (String) SetManager.getInstance().get(SetType.MESSAGE_SAVE_PATH);
                if (savepath != null && !"".equals(savepath)) {
                    File sfile = new File(savepath);
                    if (sfile != null) {
                        jfc1.setCurrentDirectory(sfile);
                    }
                }
                jfc1.showDialog(new JLabel(), "保存");
                File file = jfc1.getSelectedFile();
                if (file != null && file.isDirectory()) {
                    SetManager.getInstance().set(SetType.MESSAGE_SAVE_PATH, file.getPath());
                    jfd1.setText(file.getPath());
                }
            }
        });

        JLabel jlabe2 = new JLabel("xml目录", SwingConstants.CENTER);
        jlabe2.setSize(70, 30);
        jlabe2.setLocation(10, 70);
        jf.add(jlabe2);
        //实例化十九个个JButton对象、一个JTextField对象 
        final JTextField jfd2 = new JTextField();
        jfd2.setSize(250, 30);
        jfd2.setLocation(90, 70);
        String xmlpath = (String) SetManager.getInstance().get(SetType.MESSAGE_XML_PATH);
        if (xmlpath != null && !"".equals(xmlpath)) {
            jfd2.setText(xmlpath);
        }
        jf.add(jfd2);
        JButton jb2 = new JButton("浏览");
        jb2.setSize(70, 30);
        jb2.setLocation(350, 70);
        jf.add(jb2);
        //设置窗体是否可见 
        jf.setVisible(true);
        jb2.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser jfc2 = new JFileChooser();
                jfc2.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                String xmlpath = (String) SetManager.getInstance().get(SetType.MESSAGE_XML_PATH);
                if (xmlpath != null && !"".equals(xmlpath)) {
                    File sfile = new File(xmlpath);
                    if (null != sfile) {
                        jfc2.setCurrentDirectory(sfile);
                    }
                }
                jfc2.showDialog(new JLabel(), "保存");
                File file = jfc2.getSelectedFile();
                if (file != null && file.isDirectory()) {
                    SetManager.getInstance().set(SetType.MESSAGE_XML_PATH, file.getPath());
                    jfd2.setText(file.getPath());
                }
            }
        });
    }
}
