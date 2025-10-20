package benchmarks;


import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;


class CalcPi {
    private static final int WARMUP_N = 12000;
    private static final int WARMUP_CALLS = 20;

    public static double calcPi(int nTerms) {
        double pi = 0.0;

        for (int i = 0; i < nTerms; i++) {
            int sign = 1;

            if(i % 2 == 1)
                sign = -1;
        
            pi += sign / (2.0 * i + 1);
        }
        
        return 4 * pi;
    }

    private static void warmup() {
        for(int i = 0; i < WARMUP_CALLS; i++) {
            calcPi(WARMUP_N);
        }
    }

    private static void runTest(int nTerms) {
        warmup();

        ThreadMXBean bean = ManagementFactory.getThreadMXBean();

        // Ensure CPU time is supported
        if (bean.isCurrentThreadCpuTimeSupported()) {
            if (!bean.isThreadCpuTimeEnabled()) // Enable CPU time
                bean.setThreadCpuTimeEnabled(true);

            // Start timing
            long startTime = System.nanoTime();
            long startCpuTime = bean.getCurrentThreadCpuTime();
            
            double piApprox = calcPi(nTerms); // Execute benchmark
            
            // End timing
            long endTime = System.nanoTime();
            long endCpuTime = bean.getCurrentThreadCpuTime();

            // Calculate results in seconds
            double elapsedSeconds = (endTime - startTime) / 1_000_000_000.0;
            double cpuTime = (endCpuTime - startCpuTime) / 1_000_000_000.0;

            System.out.println(elapsedSeconds + " " + cpuTime + " " + piApprox);
        }
    }

    public static void main(String[] args) {
        if(args.length == 0) {
            System.out.println("Please provide the number of terms as a command-line argument.");
            System.exit(1);
        }

        int nTerms = 0;
    
        try {
            nTerms = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format: " + args[0]);
            System.exit(1);
        }

        if(nTerms > 0)
            runTest(nTerms);
    }   
}