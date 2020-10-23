package view;

import javax.swing.JFrame;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.border.MatteBorder;
import java.awt.Color;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Font;
import java.awt.Window;
import java.util.Vector;

import listener.ViewEventListener;
import item.Item;


@SuppressWarnings("serial")
public class View extends JFrame
{
	private final int width = 900;
	private final int height = 600;
	private final Font baseFont = new Font("Tahoma", Font.PLAIN, 16);
	
	// Les variables du UI
	private String title = "GUESS";
	
	private JPanel inforPanel;
	
	private JLabel difficultyLabel;
	private String difficultyBaseText = "Difficulty: ";
	
	private JLabel pointsLabel;
	private String pointsBaseText = "Points: ";
	
	private JLabel listLabel;
	private String listBaseText = "Current item: ";
	private int listSize;
	
	private JLabel countryLabel;
	private String countryBaseText = "Select country: ";
	
	private JComboBox<String> countryBox;
	private JButton btnNext;
	public static String triggerNextItem = "btnNext";
	
	private JPanel itemPanel;
	private JLabel ImageLabel;
	private JLabel itemNameLabel;
	private JLabel itemDescLabel;
	
	
	public View()
	{
		this.setTitle(this.title);
		this.setBounds(100, 100, this.width, this.height);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(null);
		
		this.setLocationRelativeTo(null);
		
		this.inforPanel = new JPanel();
		this.inforPanel.setBorder(new MatteBorder(1, 1, 1, 1, (Color) new Color(0, 0, 128)));
		this.inforPanel.setBounds(10, 10, 860, 50);
		this.getContentPane().add(inforPanel);
		this.inforPanel.setLayout(null);
		
		this.difficultyLabel = new JLabel();
		this.difficultyLabel.setFont(this.baseFont);
		this.difficultyLabel.setBounds(10, 10, 120, 30);
		this.inforPanel.add(difficultyLabel);
		
		this.pointsLabel = new JLabel();
		this.pointsLabel.setFont(this.baseFont);
		this.pointsLabel.setBounds(140, 10, 80, 30);
		this.inforPanel.add(pointsLabel);
		
		this.listLabel = new JLabel();
		this.listLabel.setFont(this.baseFont);
		this.listLabel.setBounds(240, 10, 150, 30);
		this.inforPanel.add(listLabel);
		
		this.countryLabel = new JLabel();
		this.countryLabel.setText(this.countryBaseText);
		this.countryLabel.setFont(this.baseFont);
		this.countryLabel.setBounds(470, 10, 110, 30);
		this.inforPanel.add(countryLabel);
		
		this.countryBox = new JComboBox<String>();
		this.countryBox.setBounds(590, 10, 120, 30);
		this.inforPanel.add(countryBox);
		
		this.btnNext = new JButton("Anwser");
		this.btnNext.setBounds(730, 10, 90, 30);
		this.inforPanel.add(btnNext);
		
		this.itemPanel = new JPanel();
		this.itemPanel.setBounds(10, 70, 865, 480);
		this.getContentPane().add(itemPanel);
		this.itemPanel.setLayout(null);
		
		this.ImageLabel = new JLabel("");
		this.ImageLabel.setBounds(10, 10, 565, 460);
		this.itemPanel.add(ImageLabel);
		
		this.itemNameLabel = new JLabel("Item name");
		this.itemNameLabel.setFont(this.baseFont);
		this.itemNameLabel.setBounds(600, 10, 250, 45);
		this.itemPanel.add(itemNameLabel);
		
		this.itemDescLabel = new JLabel("Item description");
		this.itemDescLabel.setFont(this.baseFont);
		this.itemDescLabel.setBounds(600, 80, 250, 180);
		this.itemPanel.add(itemDescLabel);
		
		// En theorie il y aurait un event "startup"
	}
	
	// La fonction qui fill les options prisent au lancement
	public void startup(String difficulty, int listSize, Vector<String> countryList, Item item)
	{
		difficultyLabel.setText(this.difficultyBaseText + difficulty);
		pointsLabel.setText(this.pointsBaseText + 0);
		this.listSize = listSize;
		listLabel.setText(this.listBaseText + 1 + " / " + this.listSize);
		
		this.fillCountryBox(countryList);
		
		this.setNextItem(item);
	}
	
	// La fonction qui s'occupe de faire les changements du UI quand necessaire
	public void refresh(int currentItemNb, Item item)
	{
		listLabel.setText(this.listBaseText + (currentItemNb+1) + " / " + this.listSize);
		this.setNextItem(item);
	}
	
	public void refresh(int points)
	{
		pointsLabel.setText(this.pointsBaseText + points);
	}
	
	public String getSelectedCountry()
	{
		return this.countryBox.getItemAt(this.countryBox.getSelectedIndex());
		//return (String) this.countryBox.getSelectedItem();
	}
	
	private void setNextItem(Item item)
	{
		this.itemNameLabel.setText(item.getName());
		this.itemDescLabel.setText(item.getDescription());
		this.ImageLabel.setIcon(item.getImage());
		
		this.countryBox.setSelectedItem(null);
		
	}
	
	// Rempli le combo-box qui contient les choix de pays
	private void fillCountryBox(Vector<String> countryList)
	{
		for (String country : countryList)
		{
			this.countryBox.addItem(country);
		}
		// Pour que rien ne soit selectionne par defaut
		this.countryBox.setSelectedItem(null);
	}
	
	// La fonction qui rajoute l'ecouteur aux elements de la vue
	public void addListener(ViewEventListener listener)
	{
		this.btnNext.addActionListener(listener);
		listener.addTrigger((JComponent)this.btnNext, View.triggerNextItem);
	}
	
	// Le pop-up d'erreur quand aucun pays n'est selectionne
	public void selectCountryError()
	{
		JOptionPane.showMessageDialog(View.this, "Veuillez sélectionner un pays.");
	}
	
	// Affiche si le resultat est bon ou non selon un booleen
	public void choiceResult(boolean correctChoice)
	{
		if (correctChoice)
		{
			JOptionPane.showMessageDialog(View.this, "Vous avez fait un bon choix!");
		}
		else
		{
			JOptionPane.showMessageDialog(View.this, "Ce n'était pas le bon choix.");
		}
	}
	
	// La/les fonction(s) pour la fin du programme
	public void end()
	{
		this.btnNext.setEnabled(false);
		this.countryBox.setSelectedItem(null);
		this.countryBox.setEnabled(false);
		
		this.itemNameLabel.setText("");
		this.itemDescLabel.setText("");
		this.ImageLabel.setIcon(new ImageIcon());
		
		//
		
	}
	
	
	// static permet d'instancier sans avoir a passer par une instance de View
	public static class DifficultyWindow extends JDialog
	{
		private JRadioButton easy;
		private JRadioButton medium;
		private JRadioButton hard;
		private ButtonGroup diffBtnGroup;
		
		private JButton btnChooseDiff;
		public static String triggerDifficultyChoice = "btnChooseDiff";
		
		
		public DifficultyWindow()
		{
			this.setTitle("Difficulty Selection");
			this.setModal(true);
			this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE); // On ne peut pas fermer avec le x
			this.setBounds(0, 0, 150, 200);
			this.setLocationRelativeTo(null);
			this.getContentPane().setLayout(null);
			
			// 3 JRadioButton
			
			this.easy = new JRadioButton("Easy");
			this.easy.setBounds(10, 10, 100, 20);
			this.getContentPane().add(this.easy);
			this.medium = new JRadioButton("Medium");
			this.medium.setBounds(10, 40, 100, 20);
			this.getContentPane().add(this.medium);
			this.hard = new JRadioButton("Hard");
			this.hard.setBounds(10, 70, 100, 20);
			this.getContentPane().add(this.hard);
			
			// Pour que les 3 boutons de difficultes soient exclusifs
			// 1 button group
			this.diffBtnGroup = new ButtonGroup();
			this.diffBtnGroup.add(this.easy);
			this.diffBtnGroup.add(this.medium);
			this.diffBtnGroup.add(this.hard);
			
			this.btnChooseDiff = new JButton("Next");
			this.btnChooseDiff.setBounds(10, 100, 100, 30);
			this.getContentPane().add(this.btnChooseDiff);
			
		}
		
		// Le get du choix de la difficulte
		public int getDifficulty()
		{
			if (this.easy.isSelected())
			{
				return 1;
			}
			else if (this.medium.isSelected())
			{
				return 2;
			}
			else if (this.hard.isSelected())
			{
				return 3;
			}
			else
			{
				return 0;
			}
		}
		
		// pop-up si aucune option de difficulte n'est selectionee
		public void selectDifficultyError()
		{
			JOptionPane.showMessageDialog(View.DifficultyWindow.this, "Le choix de difficulté n'est pas valide.");
		}
		
		// Rajoute l'ecouteur au bouton et renvoit une instance de soi-meme pour que l'ecouteur puisse prendre des donnees
		public void addListener(ViewEventListener listener)
		{
			this.btnChooseDiff.addActionListener(listener);
			listener.addTrigger((JComponent)this.btnChooseDiff, View.DifficultyWindow.triggerDifficultyChoice);
			listener.addInstance((JComponent)this.btnChooseDiff, (Window)this);
		}
		
	}
}