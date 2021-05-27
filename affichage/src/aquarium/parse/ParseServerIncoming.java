package aquarium.parse;

import aquarium.Config;
import aquarium.Connection;
import java.io.IOException;

public class ParseServerIncoming implements Runnable {

    Connection connection;
    public ParseServerIncoming(Connection c) {
        this.connection = c;
    }

    @Override
    public void run() {
        try {
            while (this.connection.client.getSocket().isConnected()) {
                final String scanned = this.connection.client.in.readLine();
                this.connection.logger.info("< " + scanned);
                if (scanned.startsWith("list")) {
                    if (this.connection.commandsList.getLast().equals("getFishes")) {
                        Parser.parseGetFishes(scanned, connection);
                        this.connection.commandsList.addLast("getFishesContinuously");
                        this.connection.sendCommand("getFishesContinuously");
                    } else {
                        // In this case, we know that the last request must've been getFishesContinuously.
                        Parser.parseFishList(scanned, this.connection);
                    }
                } else if (scanned.startsWith("bye") || scanned.startsWith("no greeting")) {
                    this.connection.endConnection();
                    System.exit(0);
                } else if (scanned.startsWith("greeting")) {
                    Parser.parseGreeting(scanned);
                    this.connection.commandsList.addLast("getFishes");
                    this.connection.sendCommand("getFishes");
                    this.connection.launch();
                } else if (scanned.startsWith("\t->OK")) {
                    this.connection.prompt.addResponse(scanned.replace("$", "\n"));
                } else if (scanned.startsWith("OK")) {
                    this.connection.prompt.addResponse(scanned);
                    String command = this.connection.commandsList.getLast();
                    if (command.startsWith("addFish")) {
                        Parser.parseAddFish(command, this.connection);
                    } else if (command.startsWith("delFish")) {
                        this.connection.delFish(command.split(" ")[1]);
                    }
                } else if (scanned.startsWith("NOK")) {
                    this.connection.prompt.addResponse(scanned);
                }
            }
        }

        catch (IOException e) {
            this.connection.logger.severe("No server is listening on port " + Config.properties.getProperty("controller-port"));
        }
    }
}
