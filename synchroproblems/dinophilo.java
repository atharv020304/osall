

package OsJava.sync;

import java.util.concurrent.Semaphore;

class DiningPhilosopher {
    static final int NUM_PHILOSOPHERS = 5;
    static Semaphore[] forks = new Semaphore[NUM_PHILOSOPHERS];
    static Semaphore mutex = new Semaphore(1);

    static class Philosopher extends Thread {
        int id;
        Semaphore leftFork;
        Semaphore rightFork;

        Philosopher(int id, Semaphore leftFork, Semaphore rightFork) {
            this.id = id;
            this.leftFork = leftFork;
            this.rightFork = rightFork;
        }

        void think() throws InterruptedException {
            System.out.println("Philosopher " + id + " is thinking.");
            Thread.sleep(3000);
        }

        void eat() throws InterruptedException {
            System.out.println("Philosopher " + id + " is eating.");
            Thread.sleep(3000);
        }

        @Override
        public void run() {
            try {
                while (true) {
                    think();
                    mutex.acquire();
                    leftFork.acquire();
                    rightFork.acquire();
                    eat();
                    rightFork.release();
                    leftFork.release();
                    mutex.release();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            forks[i] = new Semaphore(1);
        }

        Philosopher[] philosophers = new Philosopher[NUM_PHILOSOPHERS];
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosophers[i] = new Philosopher(i, forks[i], forks[(i + 1) % NUM_PHILOSOPHERS]);
            philosophers[i].start();
        }
    }
}



