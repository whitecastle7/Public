package item;

import javax.swing.ImageIcon;
//import java.awt.image.BufferedImage;


public class Item
{
	private String name;
	private String country;
	private String continent;
	private String description;
	private ImageIcon image;
	private String imgDesc; // Si l'image ne load pas
	// Pour une option de skip ou un re-shuffle
	private boolean passed = false;
	
	
	public Item()
	{
		
	}
	
	public Item(String name, String country, String continent, String description, ImageIcon image)
	{
		this.name = name;
		this.country = country;
		this.continent = continent;
		this.description = description;
		this.image = image;
	}
	
	public void setPassed()
	{
		this.passed = true;
	}
	
	public void setPassed(boolean repass)
	{
		this.passed = repass;
	}
	
	public boolean isPassed()
	{
		return this.passed;
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public String getCountry()
	{
		return this.country;
	}
	
	public String getContinent()
	{
		return this.continent;
	}
	
	public ImageIcon getImage()
	{
		return this.image;
	}
	
	public String getImageDesc()
	{
		return this.imgDesc;
	}

	public String getDescription()
	{
		return this.description;
	}
	
	// hard mode
	public void setDescription()
	{
		this.description = null;
	}
	
	
}