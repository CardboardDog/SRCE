package SRCEedit;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import javax.swing.*;
import SRCEedit.ColorPalette;
public class TexturesTab extends JPanel{
    public TexturesTab(){
        JPanel textureSelect = new JPanel();
        JPanel canvas = new JPanel();
        JPanel colorSelect = new JPanel();
        JPanel colorPalette = new JPanel();
        JPanel drawMode = new JPanel();
        JRadioButton eraseMode = new JRadioButton("Eraser");
        JRadioButton penMode = new JRadioButton("Pencil");
        JRadioButton rectMode = new JRadioButton("Rectangle");
        ButtonGroup modeGroup = new ButtonGroup();
        ButtonGroup texGroup = new ButtonGroup();
        JPanel texturePanel = new JPanel();
        texturePanel.setLayout(new BoxLayout(texturePanel, BoxLayout.Y_AXIS));
        JScrollPane textureScroll = new JScrollPane(texturePanel);
        JPanel textureOptions = new JPanel();
        JButton deleteTex = new JButton("Del");
        JButton newTex = new JButton("New");
        JButton renameTex = new JButton("Ren");
        textureSelect.setLayout(new BoxLayout(textureSelect, BoxLayout.Y_AXIS));
        textureOptions.add(deleteTex);
        textureOptions.add(newTex);
        textureOptions.add(renameTex);
        textureScroll.setPreferredSize(new Dimension(125,200));
        textureScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        for(int x=0;x<45;x++){
            JRadioButton exampleButton = new JRadioButton("example texture: "+String.valueOf(x+1));
            texGroup.add(exampleButton);
            if(x==0)exampleButton.setSelected(true);
            texturePanel.add(exampleButton); // will be replaced with real texture loading later
        }
        colorPalette.setLayout(new GridLayout(5,5));
        colorPalette.setMaximumSize(new Dimension(125,125));
        for(int color=0;color<20;color++){
            JButton paletteButton = new JButton();
            paletteButton.setBackground(ColorPalette.colors[color]);
            colorPalette.add(paletteButton);
        }
        colorSelect.setLayout(new BoxLayout(colorSelect, BoxLayout.Y_AXIS));
        modeGroup.add(rectMode);
        modeGroup.add(eraseMode);
        modeGroup.add(penMode);
        penMode.setSelected(true);
        canvas.setBackground(Color.DARK_GRAY);
        drawMode.add(rectMode);
        drawMode.add(eraseMode);
        drawMode.add(penMode);
        colorSelect.add(colorPalette);
        colorSelect.add(drawMode);
        textureSelect.add(textureScroll);
        textureSelect.add(textureOptions);
        textureSelect.setMaximumSize(new Dimension(125,getMaximumSize().height));
        colorSelect.setMaximumSize(new Dimension(125,getMaximumSize().height));
        this.setLayout(new BoxLayout(this,BoxLayout.X_AXIS));
        this.add(textureSelect);
        this.add(canvas);
        this.add(colorSelect);
        drawMode.setLayout(new BoxLayout(drawMode, BoxLayout.Y_AXIS));
    }
}