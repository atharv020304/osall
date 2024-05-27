
package OsJava.sync;

import java.util.concurrent.Semaphore;

class ReaderWriter {
    static Semaphore mutex = new Semaphore(1);
    static Semaphore rw_mutex = new Semaphore(1);
    static int readers_count = 0;
    static volatile boolean running = true;

    static class Reader extends Thread {
        int readerID;

        Reader(int readerID) {
            this.readerID = readerID;
        }

        public void run() {
            while (running) {
                try {
                    mutex.acquire();
                    readers_count++;
                    if (readers_count == 1) {
                        rw_mutex.acquire();
                    }
                    mutex.release();

                    System.out.println("Reader " + readerID + " is reading.");

                    mutex.acquire();
                    readers_count--;
                    if (readers_count == 0) {
                        rw_mutex.release();
                    }
                    mutex.release();

                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class Writer extends Thread {
        int writerID;

        Writer(int writerID) {
            this.writerID = writerID;
        }

        public void run() {
            while (running) {
                try {
                    rw_mutex.acquire();

                    System.out.println("Writer " + writerID + " is writing.");

                    rw_mutex.release();

                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        final int NUM_READERS = 5;
        final int NUM_WRITERS = 2;

        Reader[] readers = new Reader[NUM_READERS];
        Writer[] writers = new Writer[NUM_WRITERS];

        for (int i = 0; i < NUM_READERS; i++) {
            readers[i] = new Reader(i + 1);
            readers[i].start();
        }

        for (int i = 0; i < NUM_WRITERS; i++) {
            writers[i] = new Writer(i + 1);
            writers[i].start();
        }

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        running = false;

        for (Reader reader : readers) {
            try {
                reader.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for (Writer writer : writers) {
            try {
                writer.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

