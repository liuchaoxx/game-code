/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 *
 * @author Administrator
 */
public class GentSelectUI implements GentUI{

    //定义一个计算器界面的方法 
    @Override
    public void initGUI() {
        //实例化一个JFrame类的对象 
        final javax.swing.JFrame jf = new javax.swing.JFrame();
        //设置窗体的标题属性 
        jf.setTitle("代码生成器");
        //设置窗体的大小属性 
        jf.setSize(200, 250);
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
        java.awt.GridLayout gr = new java.awt.GridLayout(3, 1);
        //设置窗体的布局方式为网格布局 
        jf.setLayout(gr);
        //实例化十九个个JButton对象、一个JTextField对象 
        javax.swing.JButton jb1 = new javax.swing.JButton("消息");
        javax.swing.JButton jb2 = new javax.swing.JButton("数据库");
        javax.swing.JButton jb3 = new javax.swing.JButton("设置");
        jf.add(jb1);
        jf.add(jb2);
        jf.add(jb3);
        //设置窗体是否可见 
        jf.setVisible(true);

        jb1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                GentUI ui = new GentProtoUI();
                jf.setVisible(false);
                ui.initGUI();
            }
        });
        jb2.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                GentUI ui = new GentDBUI();
                jf.setVisible(false);
                ui.initGUI();
            }
        });
        jb2.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
            }
        });
    }
}
