package aquarium.gui;

import aquarium.Config;
import aquarium.Connection;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Prompt {

    public Stage stage;
    Connection connection;
    TextArea response;

    public Prompt(Connection connection) {
        this.connection = connection;
        this.stage = new Stage();
        this.stage.setX(600);
        this.stage.setY(300);
        this.stage.setOnCloseRequest(e -> {
            this.connection.endConnection();
            Platform.exit();
            System.exit(0);
        });
        VBox box = new VBox(5);
        TextField command = new TextField();
        command.setStyle("-fx-text-box-border: #00ff00; -fx-focus-color: #00ff00; -fx-control-inner-background: #2d2d2d; -fx-font-family: Consolas; -fx-highlight-fill: #00ff00; -fx-highlight-text-fill: #2d2d2d; -fx-text-fill: #00ff00; ");
        this.response = new TextArea();
        this.response.setPrefRowCount(10);
        this.response.setEditable(false);
        this.response.setStyle("-fx-text-box-border: #00ff00; -fx-focus-color: #00ff00; -fx-control-inner-background: #2d2d2d; -fx-font-family: Consolas; -fx-highlight-fill: #00ff00; -fx-highlight-text-fill: #2d2d2dff; -fx-text-fill: #00ff00; ");
        Button exampleButton = new Button("Run example");
        exampleButton.setStyle("-fx-background-color: #204d7b; -fx-text-fill: white;");
        exampleButton.setOnAction(actionEvent -> {
            try {
                File commandsExample = new File("resources/data/example.cmds");
                Scanner reader = new Scanner(commandsExample);
                while (reader.hasNextLine()) {
                    this.connection.sendCommand(reader.nextLine());
                }
                reader.close();
            } catch (FileNotFoundException e) {
                System.out.println("file not found.");
                e.printStackTrace();
            }
        });

        Button logoutButton = new Button("log out");
        logoutButton.setStyle("-fx-background-color: #842f2f; -fx-text-fill: white;");
        logoutButton.setOnAction(actionEvent -> {
            this.connection.sendCommand("log out");
        });

        Button statusButton = new Button("status");
        statusButton.setStyle("-fx-background-color: rgba(5,88,5,0.87); -fx-text-fill: white;");
        statusButton.setOnAction(actionEvent -> {
            this.connection.sendCommand("status");
        });

        GridPane buttons = new GridPane();
        buttons.setAlignment(Pos.CENTER);
        buttons.setHgap(5);
        buttons.add(exampleButton, 0, 0, 1, 1);
        buttons.add(statusButton, 1, 0, 1, 1);
        buttons.add(logoutButton, 2, 0, 1, 1);
        box.getChildren().addAll(command, this.response, buttons);
        box.setAlignment(Pos.CENTER);
        box.setStyle("-fx-background-color : #2d2d2d;");
        this.response.setScrollTop(0);
        command.setOnKeyPressed( event -> {
            if( event.getCode() == KeyCode.ENTER ) {
                this.connection.commandsList.addLast(command.getText());
                this.connection.sendCommand(command.getText());
                addCommand(command.getText());
                command.setText("");
            }
        });
        this.stage.setScene(new Scene(box, 400, 250));
    }

    public void addResponse(String str) {
        this.response.appendText("< " + str + "\n");
    }

    public void addCommand(String str) {
        this.response.appendText("> " + str + "\n");
    }
}
