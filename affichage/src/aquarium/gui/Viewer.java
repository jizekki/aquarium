package aquarium.gui;

import aquarium.Config;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Viewer {
    public Stage stage;
    public BorderPane pane;

    public Viewer(Stage primaryStage){
        this.stage = primaryStage;
        this.stage.setHeight(Integer.parseInt(Config.properties.getProperty("viewer-height")));
        this.stage.setWidth(Integer.parseInt(Config.properties.getProperty("viewer-width")));
        this.stage.setX(100);
        this.stage.setY(100);
        this.pane = new BorderPane();
        this.pane.setStyle("-fx-background-image: url('file:resources/images/background.jpg'); -fx-background-repeat: no-repeat; -fx-background-size: cover, auto;");
        Scene scene = new Scene(this.pane, stage.getWidth(), stage.getHeight());
        this.stage.setScene(scene);

    }
}
