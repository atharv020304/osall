import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

class ProducerConsumer {
    static final int BUFFER_SIZE = 5;
    static Semaphore mutex = new Semaphore(1);
    static Semaphore full = new Semaphore(0);
    static Semaphore empty = new Semaphore(BUFFER_SIZE);
    static Queue<Integer> buffer = new LinkedList<>();

    static class Producer extends Thread {
        public void run() {
            for (int i = 0; i < 5; i++) {
                try {
                    empty.acquire();
                    mutex.acquire();
                    buffer.add(i);
                    System.out.println("Producer produced item " + i);
                    mutex.release();
                    full.release();
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
                    int item = buffer.poll();
                    System.out.println("Consumer consumed item " + item);
                    mutex.release();
                    empty.release();
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