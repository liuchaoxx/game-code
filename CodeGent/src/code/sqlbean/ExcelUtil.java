/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package code.sqlbean;

import code.common.Common;
import code.gent.CodeUtil;
import code.message.Bean;
import code.message.ClassField;
import code.set.SetManager;
import code.set.SetType;
import freemarker.template.utility.StringUtil;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class ExcelUtil {

    /**
     * read the Excel file
     *
     * @param path the path of the Excel file
     * @return
     * @throws IOException
     */
    public static List<Bean> readExcel(String path) throws IOException {
        if (path == null || Common.EMPTY.equals(path)) {
            return null;
        } else {
            String postfix = getPostfix(path);
            if (!Common.EMPTY.equals(postfix)) {
                if (Common.OFFICE_EXCEL_2003_POSTFIX.equals(postfix)) {
                    return readXls(path);
                } else if (Common.OFFICE_EXCEL_2010_POSTFIX.equals(postfix)) {
                    return readXlsx(path);
                }
            } else {
                System.out.println(path + Common.NOT_EXCEL_FILE);
            }
        }
        return null;
    }

    /**
     * get postfix of the path
     *
     * @param path
     * @return
     */
    public static String getPostfix(String path) {
        if (path == null || Common.EMPTY.equals(path.trim())) {
            return Common.EMPTY;
        }
        if (path.contains(Common.POINT)) {
            return path.substring(path.lastIndexOf(Common.POINT) + 1, path.length());
        }
        return Common.EMPTY;
    }

    /**
     * Read the Excel 2010
     *
     * @param path the path of the excel file
     * @return
     * @throws IOException
     */
    public static List<Bean> readXlsx(String path) throws IOException {
        System.out.println(Common.PROCESSING + path);
        InputStream is = new FileInputStream(path);
        XSSFWorkbook xssfWorkbook = new XSSFWorkbook(is);
        List<Bean> list = new ArrayList<Bean>();
        for (int numSheet = 0; numSheet < xssfWorkbook.getNumberOfSheets(); numSheet++) {
            XSSFSheet xssfSheet = xssfWorkbook.getSheetAt(numSheet);
            int max_row_num = xssfSheet.getLastRowNum();
            if (max_row_num >= 3) {
                XSSFRow nameXssfRow = xssfSheet.getRow(ExcelFormatType.EXCEL_NAME_ROW);
                short totleCellCount = nameXssfRow.getLastCellNum();
                if (totleCellCount > 1) {
                    Bean bean = new Bean();
                    bean.setName(xssfSheet.getSheetName());
                    bean.setDescribe(path);
                    for (int cellNum = 0; cellNum < totleCellCount; cellNum++) {
                        XSSFCell hssfCell = nameXssfRow.getCell(cellNum);
                        if (hssfCell != null) {
                            ClassField cfield = new ClassField();
                            cfield.setName(hssfCell.getStringCellValue());
                            cfield.setDescribe(xssfSheet.getRow(ExcelFormatType.EXCEL_DESC_ROW).getCell(cellNum).getStringCellValue());
                            cfield.setPtype(xssfSheet.getRow(ExcelFormatType.EXCEL_TYPE_ROW).getCell(cellNum).getStringCellValue());
                            XSSFCell typeCell = xssfSheet.getRow(ExcelFormatType.EXCEL_KEY_ROW).getCell(cellNum);
                            cfield.setCtype(typeCell == null ? "0" : "1");
                            bean.getField().add(cfield);
                        }
                    }
                    list.add(bean);
                }
            }
        }
        return list;
    }

    /**
     * Read the Excel 2003-2007
     *
     * @param path the path of the Excel
     * @return
     * @throws IOException
     */
    public static List<Bean> readXls(String path) throws IOException {
        InputStream is = new FileInputStream(path);
        HSSFWorkbook hssfWorkbook = new HSSFWorkbook(is);
        List<Bean> list = new ArrayList<Bean>();
        for (int numSheet = 0; numSheet < hssfWorkbook.getNumberOfSheets(); numSheet++) {
            HSSFSheet hssfSheet = hssfWorkbook.getSheetAt(numSheet);
            int max_row_num = hssfSheet.getLastRowNum();
            if (max_row_num >= 3) {
                HSSFRow nameHssfRow = hssfSheet.getRow(ExcelFormatType.EXCEL_NAME_ROW);
                short totleCellCount = nameHssfRow.getLastCellNum();
                if (totleCellCount > 1) {
                    Bean bean = new Bean();
                    bean.setName(hssfSheet.getSheetName());
                    bean.setDescribe(path);
                    for (int cellNum = 0; cellNum < totleCellCount; cellNum++) {
                        HSSFCell hssfCell = nameHssfRow.getCell(cellNum);
                        if (hssfCell != null) {
                            ClassField cfield = new ClassField();
                            cfield.setName(hssfCell.getStringCellValue());
                            cfield.setDescribe(hssfSheet.getRow(ExcelFormatType.EXCEL_DESC_ROW).getCell(cellNum).getStringCellValue());
                            cfield.setPtype(hssfSheet.getRow(ExcelFormatType.EXCEL_TYPE_ROW).getCell(cellNum).getStringCellValue());
                            HSSFCell typeCell = hssfSheet.getRow(ExcelFormatType.EXCEL_KEY_ROW).getCell(cellNum);
                            cfield.setCtype(typeCell == null ? "0" : "1");
                            bean.getField().add(cfield);
                        }
                    }
                    list.add(bean);
                }
            }
        }
        return list; 
    }

   public static String generator_sqlbean(String path, String filename, String template) throws IOException {
        String excel_path = (String) SetManager.getInstance().get(SetType.BEAN_EXCEL_PATH);
        if (excel_path == null || "".equals(excel_path)) {
            return Common.EXCEL_PATH_ERROR;
        }
        CodeUtil util = new CodeUtil(Common.FTL_PATH);
        List<Bean> readBeanList = readExcel(excel_path + filename);
        for (Bean bean : readBeanList) {
            util.buildFile(bean.buildMap(), template, path, toFirstUpperCase(bean.getName()+".h"));
        }
        return Common.GENT_SUCCESS;
    }
   
     public static String toFirstUpperCase(String name) {
        char[] cs=name.toCharArray();
        cs[0]-=32;
        return String.valueOf(cs);
    }
}
