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
public class LevelsTab extends JPanel{
    public LevelsTab(){
        JPanel levelSelect = new JPanel();
        ButtonGroup levGroup = new ButtonGroup();
        JPanel levelPanel = new JPanel();
        levelPanel.setLayout(new BoxLayout(levelPanel, BoxLayout.Y_AXIS));
        JScrollPane levelScroll = new JScrollPane(levelPanel);
        JPanel levelOptions = new JPanel();
        JButton deleteLev = new JButton("Del");
        JButton newLev = new JButton("New");
        JButton renameLev = new JButton("Ren");
        levelSelect.setLayout(new BoxLayout(levelSelect, BoxLayout.Y_AXIS));
        levelOptions.add(deleteLev);
        levelOptions.add(newLev);
        levelOptions.add(renameLev);
        levelScroll.setPreferredSize(new Dimension(125,200));
        levelScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        for(int x=0;x<45;x++){
            JRadioButton exampleButton = new JRadioButton("example level: "+String.valueOf(x+1));
            levGroup.add(exampleButton);
            if(x==0)exampleButton.setSelected(true);
            levelPanel.add(exampleButton); // will be replaced with real level loading later
        }
        levelSelect.add(levelScroll);
        levelSelect.add(levelOptions);
        levelSelect.setMaximumSize(new Dimension(125,getMaximumSize().height));
        this.add(levelSelect);
        JPanel level = new JPanel();
        level.setBackground(Color.BLACK);
        this.add(level);
        JPanel drawMode = new JPanel();
        JRadioButton flattenMode = new JRadioButton("Flatten");
        JRadioButton raiseMode = new JRadioButton("Raise");
        JRadioButton rectMode = new JRadioButton("Lower");
        ButtonGroup modeGroup = new ButtonGroup();
        modeGroup.add(rectMode);
        modeGroup.add(flattenMode);
        modeGroup.add(raiseMode);
        drawMode.add(rectMode);
        drawMode.add(flattenMode);
        drawMode.add(raiseMode);
        flattenMode.setSelected(true);
        JSlider modify = new JSlider(0,35,1);
        modify.setMinorTickSpacing(1);
        modify.setMajorTickSpacing(5);
        modify.setPaintTicks(true);
        modify.setPaintTrack(true);
        modify.setPaintLabels(true);
        drawMode.add(modify);
        JButton roofHeight = new JButton("Roof");
        JButton floorHeight = new JButton("Floor");
        JButton blockColor = new JButton("Color");
        JButton wallTexture = new JButton("Texture");        
        drawMode.add(roofHeight);
        drawMode.add(floorHeight);
        drawMode.add(blockColor);
        drawMode.add(wallTexture);
        JPanel modeSelect = new JPanel();
        modeSelect.add(drawMode);
        modeSelect.setMaximumSize(new Dimension(125,getMaximumSize().height));
        this.add(modeSelect);
        drawMode.setLayout(new BoxLayout(drawMode, BoxLayout.Y_AXIS));
        this.setLayout(new BoxLayout(this,BoxLayout.X_AXIS));
    }   
}
