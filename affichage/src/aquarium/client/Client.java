package aquarium.client;

import aquarium.Config;

import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Client {
    private Socket socket;
    public PrintWriter out;
    public BufferedReader in;
    private static final Logger logger = Logger.getLogger(Client.class.getName());

    public Client() {
        try {
            this.socket = new Socket(InetAddress.getByName( Config.properties.getProperty("controller-address")), Integer.parseInt(Config.properties.getProperty("controller-port")));
            logger.log(Level.INFO, "Connected to server "+ InetAddress.getByName( Config.properties.getProperty("controller-address")) + " on port " + Integer.parseInt(Config.properties.getProperty("controller-port")));
            this.out = new PrintWriter(this.socket.getOutputStream(), true);
            this.in = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        }catch (IOException e){
            logger.log(Level.SEVERE, "The server is not running or can't be reached");
            System.exit(0);
        }
    }

    public Socket getSocket() {return socket;}
}
