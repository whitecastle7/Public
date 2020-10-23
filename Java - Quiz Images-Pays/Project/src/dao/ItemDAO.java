package dao;

import java.io.FileInputStream;
import java.io.InputStream;
import org.apache.poi.ss.usermodel.WorkbookFactory;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
//import java.sql.Connection; //
import java.util.Vector;
import javax.swing.ImageIcon;

//import dao.ConnectionDAO;
import item.Item;


public class ItemDAO
{
	static public Vector<Item> getItemList()
	{
		//Connection c = ConnectionDAO.getConnection();
		
		Vector<Item> items = new Vector<Item>();
		//items.add(new Item());
		//items.add(new Item());
		String basePath = "images/";
		
        try
        {
        	InputStream inp = new FileInputStream ("Items.xlsx");
        	XSSFWorkbook doc = (XSSFWorkbook)WorkbookFactory.create(inp);
        	XSSFSheet sheet = doc.getSheetAt(0); // feuilles commence a 0

        	int nbRows = sheet.getLastRowNum();
        	// On skip la premiere ligne qui continent le titre des colonnes
        	for (int i = 1; i <= nbRows; ++i)
        	{
        		// Get une ligne
        		XSSFRow row = sheet.getRow(i);
        		
        		XSSFCell cell = row.getCell(0);
        		String name = cell.getStringCellValue();
        		System.out.print(name + " | ");

        		cell = row.getCell(1);
        		String country = cell.getStringCellValue();
        		System.out.print(country + " | ");
        		
        		cell = row.getCell(2);
        		String continent = cell.getStringCellValue();
        		System.out.print(continent + " | ");
        		
        		cell = row.getCell(3);
        		String desc = cell.getStringCellValue();
        		System.out.println(desc);
        		
        		cell = row.getCell(4);
        		String imgPath = basePath + cell.getStringCellValue();
        		ImageIcon img = new ImageIcon(imgPath);
        		
        		Item item = new Item(name, country, continent, desc, img);
        		items.add(item);
        	}
        	inp.close();
        }
        catch (Exception f)
        {
        	f.printStackTrace();
        }
		
		//ConnectionDAO.releaseConnection();
		//c = null;
		return items;
	}
	
	static public Vector<String> getCountryList()
	{
		//Connection c = ConnectionDAO.getConnection();
		
		Vector<String> countries = new Vector<String>();
		countries.add("Canada");
		countries.add("France");
		countries.add("Germany");
		countries.add("Japan");
		countries.add("South Korea");
		countries.add("Finland");
		countries.add("Denmark");
		countries.add("Sweden");
		countries.add("Switzerland");
		countries.add("Sumer");
		countries.add("Egypt");
		//
		
		//ConnectionDAO.releaseConnection();
		//c = null;
		return countries;
	}
	
}