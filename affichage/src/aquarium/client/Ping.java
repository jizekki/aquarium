package aquarium.client;
import aquarium.Config;
import java.io.PrintWriter;
import java.util.logging.Logger;

public class Ping implements Runnable {
    public final PrintWriter out;
    public Ping(PrintWriter out) {
        this.out = out;
    }
    public final Logger logger = Logger.getLogger(Ping.class.getName());

    @Override
    public void run() {
        try {
            String pingString = "ping " + Config.properties.getProperty("controller-port");
            while (true){
                synchronized (this.out) {
                    Thread.sleep (Integer.parseInt(Config.properties.getProperty("display-timeout-value"))*1000);
                    this.out.println(pingString);
                    this.out.flush();
                    logger.info("> " + pingString);
                }
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
