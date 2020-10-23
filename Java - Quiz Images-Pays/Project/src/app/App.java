package app;

import java.util.Collections;
import java.util.Vector;

import dao.ItemDAO;
import item.Item;
import view.View;
import listener.ViewEventListener;


public class App
{
	private View view;
	private ViewEventListener listener;
	
	private int points;
	private int difficulty;
	private Vector<Integer> difficultyList = new Vector<>();
	
	private Vector<Item> itemList;
	private int listSize;
	private int currentItemNb;
	
	private Vector<String> countries;
	private int countriesAmount;
	
	
	public App()
	{
		// On rempli les variables d'instances de l'app
		this.itemList = ItemDAO.getItemList();
		Collections.shuffle(itemList);
		this.listSize = this.itemList.size();
		
		this.countries = ItemDAO.getCountryList();
		Collections.sort(this.countries);
		this.countriesAmount = this.countries.size();
		
		this.currentItemNb = 0;
		this.points = 0;
		
		//
		difficultyList.add(1);
		difficultyList.add(2);
		difficultyList.add(3);
		
		// Run l'app des que celle-ci est cree
		this.run();
	}
	
	// Le vrai lancement du programme
	private void run()
	{
		// On cre la vue
		this.view = new View();
		this.view.setVisible(true);
		// On cre l'ecouteur
		this.listener = new ViewEventListener(this.view, this);
		this.view.addListener(this.listener);
		
		// Choisir la difficulte
		this.chooseDifficulty();
		// Devrait etre un evenement
		this.listener.startup();
		
		// Maintenant on n'a plus besoin de rien cote de l'app, sauf pour des get()
	}
	
	// Affiche la fenetre de choix de difficultes et y passe l'ecouteur
	private void chooseDifficulty()
	{
		View.DifficultyWindow diffChooser = new View.DifficultyWindow();
		diffChooser.addListener(this.listener);
		diffChooser.setVisible(true);
	}
	
	public void setDifficulty(int difficulty)
	{
		this.difficulty = difficulty;
	}
	
	public Vector<Integer> getDifficultyList()
	{
		return this.difficultyList;
	}
	
	public int getPoints()
	{
		return this.points;
	}
	
	public void incrementPoints()
	{
		this.points += 10;
	}
	
	public String getDifficulty()
	{
		switch(this.difficulty)
		{
			case 1: return "easy";
			case 2: return "medium";
			case 3: return "hard";
			default: return null;
		}
	}
	
	// Wipe les descriptions de tous les items (devrait etre fait au select de la BD)
	private void setHardMode()
	{
		for(Item item : this.itemList)
		{
			item.setDescription();
		}
	}
	
	public int getListSize()
	{
		return this.listSize;
	}
	
	public int getCurrentItemNb()
	{
		return this.currentItemNb;
	}
	
	public Item getCurrentItem()
	{
		if (this.currentItemNb >= this.listSize)
		{
			return null;
		}
		else
		{
			return this.itemList.get(this.currentItemNb);
		}
	}
	
	private void incrementCurrentItemNb()
	{
		this.currentItemNb += 1;
	}
	
	public Vector<String> getCountryList()
	{
		return this.countries;
	}
	
	public int getNumberOfCountries()
	{
		return this.countriesAmount;
	}
	
	public Vector<Item> getItemList()
	{
		return this.itemList;
	}
	
	public Item getNextItem()
	{
		// L'item est passe, alors on lui met un check
		this.itemList.get(this.currentItemNb).setPassed();
		
		// On incremente l'index a utiliser
		this.incrementCurrentItemNb();
		
		// On regarde si l'index est toujours dans les bonnes bornes
		if (this.currentItemNb >= this.listSize)
		{
			return null;
		}
		else
		{
			return this.itemList.get(this.currentItemNb);
		}
	}
	
}