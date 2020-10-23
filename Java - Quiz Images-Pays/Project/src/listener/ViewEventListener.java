package listener;

import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Hashtable;
import java.util.Vector;

import javax.swing.JComponent;

import view.View;
import view.View.DifficultyWindow;
import app.App;
import item.Item;


public class ViewEventListener implements ActionListener
{
	private App app;
	private View view; // Devrait peut-etre meme mettre la view dans instances
	private Hashtable<JComponent, String> triggers;
	private Hashtable<JComponent, Window> instances;
	
	
	public ViewEventListener(View view, App app)
	{
		this.triggers = new Hashtable<JComponent, String>();
		this.instances = new Hashtable<JComponent, Window>();
		this.view = view;
		this.app = app;
	}
	
	// Un seul call au debut du programme, devrait etre un event custom
	public void startup()
	{
		int listSize = this.app.getListSize();
		String diff = this.app.getDifficulty() == null ? "--" : this.app.getDifficulty();
		Vector<String> countryList = this.app.getCountryList();
		Item i = this.app.getCurrentItem();
		this.view.startup(diff, listSize, countryList, i);
	}
	
	// Rajoute un JComponent a la liste des potentiels declencheurs
	public void addTrigger(JComponent trigger, String name)
	{
		this.triggers.put(trigger, name);
	}
	
	// Rajouter une instance pour pouvoir y acceder lors de l'evenement
	public void addInstance(JComponent trigger, Window instance)
	{
		this.instances.put(trigger, instance);
	}
	
	// La methode appelee lors d'un evenement, la partie principale de l'ecouteur
	@Override
	public void actionPerformed(ActionEvent e)
	{
		// On regarde si le declencheur est dans la liste des potentiels declencheurs
		if (this.triggers.containsKey(e.getSource()))
		{
			// Ensuite on traite les declencheurs un par un (si x, si y, si z, etc.)
			if (this.triggers.get(e.getSource()) == View.triggerNextItem)
			{
				String selectedCountry = this.view.getSelectedCountry();
				
				// On s'assure qu'il y a bien un pays de selectionne avant de faire d'autres operations
				if (selectedCountry != null)
				{
					String correctCountry = this.app.getCurrentItem().getCountry();
					
					// Comparaison de string avec .equals
					if (selectedCountry.equals(correctCountry))
					{
						// le choix de l'usager est correct
						this.correctChoice(true);
					}
					else
					{
						// Le choix n'etait pas correct
						this.correctChoice(false);
					}
				}
				else
				{
					//afficher erreur aucune selection de pays
					this.view.selectCountryError();
				}
			}
			else if (this.triggers.get(e.getSource()) == View.DifficultyWindow.triggerDifficultyChoice)
			{
				View.DifficultyWindow wind = ((DifficultyWindow) instances.get(e.getSource()));
				int difficulty = wind.getDifficulty();
				//int difficulty = ((DifficultyWindow) instances.get(e.getSource())).getDifficulty();
				
				if (this.app.getDifficultyList().contains(difficulty))
				{
					this.app.setDifficulty(difficulty);
					wind.dispose();
					//instances.get(e.getSource()).dispose();
				}
				else
				{
					wind.selectDifficultyError();
					//((DifficultyWindow) instances.get(e.getSource())).selectDifficultyError();
				}
			}
			// autre declencheurs seraient ici
		}
		else
		{
			System.out.print("la source n'est pas dans la liste de declencheurs");
		}
	}
	
	// La fonction appelee si l'evenement produit passe au travers des filtres
	private void correctChoice(boolean correct)
	{
		this.view.choiceResult(correct);
		
		if (correct)
		{
			this.app.incrementPoints();
			int points = this.app.getPoints();
			this.view.refresh(points);
		}
		
		// Peu importe si le choix est correct ou non, on essai de passer au prochain item
		Item nextItem = this.app.getNextItem();
		if (nextItem != null)
		{
			int currentItemNb = this.app.getCurrentItemNb();
			this.view.refresh(currentItemNb, nextItem);
		}
		else
		{
			// la partie est fini
			this.end();
		}
	}
	
	// La fonction de la fin de la partie
	private void end()
	{
		this.view.end();
	}
	
}