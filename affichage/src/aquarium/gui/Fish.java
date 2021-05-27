package aquarium.gui;

import javafx.animation.*;
import javafx.application.Platform;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;
import javafx.scene.paint.Color;

import java.awt.*;

public class Fish {
    final private ImageView iv;
    private Duration duration;
    private Point destination;
    final private PathTransition pathTransition;
    String name;

    public Fish(String name, int fish_width, int fish_height, Point destination, int duration){
        this.name = name;
        this.duration = Duration.millis(duration * 1000);
        this.destination = destination;
        this.iv = new ImageView();
        String ImagePath = "file:resources/images/" + name.split("_")[0] + ".png";
        this.iv.setImage(new Image(ImagePath));
        this.iv.setFitWidth(fish_width);
        this.iv.setFitHeight(fish_height);
        this.iv.setX(destination.getX());
        this.iv.setY(destination.getY());
        Path path = new Path();
        this.pathTransition = new PathTransition();
        this.pathTransition.setDuration(this.duration);
        this.pathTransition.setPath(path);
        this.pathTransition.setNode(this.iv);
        this.pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
        this.pathTransition.setInterpolator(Interpolator.LINEAR);
    }

    public ImageView getImageView() {
        return this.iv;
    }

    public void move(){
        Platform.runLater(this.pathTransition::play);
    }
    public void stop(){
        Platform.runLater(this.pathTransition::stop);
    }

    public String getName() {
        return this.name;
    }

    public Point getDestination() { return this.destination; }

    public void updateFish(Point destination, int duration) {
        Path path = new Path();
        this.duration = Duration.millis(duration * 1000);
        if (destination.getX() == this.destination.getX() && destination.getY() == this.destination.getY()){
            this.duration = Duration.millis(0);
        }
        path.getElements().add(new MoveTo(this.destination.getX() + this.iv.getFitWidth() / 2 , this.destination.getY() + this.iv.getFitHeight() / 2));
        this.destination = destination;
        path.getElements().add(new LineTo(this.destination.getX() + this.iv.getFitWidth() / 2, this.destination.getY() + this.iv.getFitHeight() / 2));
        this.pathTransition.setPath(path);
        this.pathTransition.setDuration(this.duration);
    }
}
