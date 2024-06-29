import javax.swing.JFrame;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.WindowConstants;
import SRCEedit.*;
class Editor{
    public static void main(String args[]){
        /*try{ // the GTK theme currently breaks the color palette ):
            if(System.getProperty("os.name").contains("Linux")){
                UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel");
            }else{
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            }
        }catch(Exception e){} // ignore and use ugly default*/
        JFrame window = new JFrame();
        JTabbedPane tabs = new JTabbedPane();
        SettingsTab settingsTab = new SettingsTab();
        ExportTab exportTab = new ExportTab();
        TexturesTab texturesTab = new TexturesTab();
        LevelsTab levelsTab = new LevelsTab();
        tabs.addTab("Textures",texturesTab);
        tabs.addTab("Levels",levelsTab);
        tabs.addTab("Settings",settingsTab);
        tabs.addTab("Import/Export",exportTab);
        window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        window.add(tabs);
        window.setVisible(true);
        window.setSize(400,400);
    }
} 
