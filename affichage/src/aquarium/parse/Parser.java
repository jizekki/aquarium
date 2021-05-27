package aquarium.parse;

import aquarium.Config;
import aquarium.Connection;
import aquarium.gui.Fish;
import java.awt.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Parser {


    public static void parseGetFishes(String str, Connection connection) {
        String regex = "\\[(?<name>[a-zA-Z]+) at (?<positionX>\\d+)x(?<positionY>\\d+),(?<fishWidth>\\d+)x(?<fishHeight>\\d+),(?<duration>\\d+)]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("list ", ""));
        String name;
        while (matcher.find()) {
            name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth")) * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100;
            int fish_height = Integer.parseInt(matcher.group("fishHeight")) * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100;
            int duration = Integer.parseInt(matcher.group("duration"));
            Point position = new Point(Integer.parseInt(matcher.group("positionX")) * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100, Integer.parseInt(matcher.group("positionY")) * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100);
            Fish fish = new Fish(name, fish_width, fish_height, position, duration);
            connection.addFish(fish);
        }
    }

    public static void parseFishList(String str, Connection connection) {
        String regex = "\\[(?<name>[a-zA-Z_0-9]+) at (?<destinationX>\\d+)x(?<destinationY>\\d+),(?<fishWidth>\\d+)x(?<fishHeight>\\d+),(?<duration>\\d+)]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("list ", ""));
        String name;
        while (matcher.find()) {
            name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"))  * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100;
            int fish_height = Integer.parseInt(matcher.group("fishHeight")) * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100;
            Point destination = new Point(Integer.parseInt(matcher.group("destinationX")) * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100, Integer.parseInt(matcher.group("destinationY")) * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100);
            int duration = Integer.parseInt(matcher.group("duration"));
            Fish oldFish = connection.findFish(name);
            if (oldFish == null){
                connection.addFish(new Fish(name, fish_width, fish_height, destination, duration));
            }else{
                connection.updateFish(oldFish, destination, duration);
            }
        }
    }

    public static void parseGreeting(String str) {
        Config.properties.setProperty("id", str.split("\\s")[1]);
    }

    public static void parseAddFish(String str, Connection connection) {

        String regex = "(?<name>[a-zA-Z_0-9]+) at (?<positionX>\\d+)x(?<positionY>\\d+), (?<fishWidth>\\d+)x(?<fishHeight>\\d+), ([a-zA-Z]+)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("addFish ", ""));
        while (matcher.find()) {
            String name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"))  * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100;
            int fish_height = Integer.parseInt(matcher.group("fishHeight"))  * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100;
            Point position = new Point(Integer.parseInt(matcher.group("positionX"))  * Integer.parseInt(Config.properties.getProperty("viewer-width")) / 100, Integer.parseInt(matcher.group("positionY"))  * Integer.parseInt(Config.properties.getProperty("viewer-height")) / 100);
            Fish fish = new Fish(name, fish_width, fish_height, position, 0);
            connection.addFish(fish);
        }

    }
}
