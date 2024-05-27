
package OsJava.sync;

import java.util.concurrent.Semaphore;

class ProducerConsumer {
    static final int BUFFER_SIZE = 5;
    static Semaphore mutex = new Semaphore(1);
    static Semaphore full = new Semaphore(0);
    static Semaphore empty = new Semaphore(BUFFER_SIZE);

    static class Producer extends Thread {
        public void run() {
            for (int i = 0; i < 5; i++) {
                try {
                    empty.acquire();
                    mutex.acquire();
                    System.out.println("Producer produced item " + i);
                    mutex.release();
                    full.release();
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class Consumer extends Thread {
        public void run() {
            for (int i = 0; i < 5; i++) {
                try {
                    full.acquire();
                    mutex.acquire();
                    System.out.println("Consumer consumed item " + i);
                    mutex.release();
                    empty.release();
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        Producer producer = new Producer();
        Consumer consumer = new Consumer();
        producer.start();
        consumer.start();
    }
}



