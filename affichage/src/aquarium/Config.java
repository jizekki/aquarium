package aquarium;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class Config {
    public static Properties properties;

    static {
        try {
            properties = new Properties();
            properties.load(new FileInputStream("affichage.cfg"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
