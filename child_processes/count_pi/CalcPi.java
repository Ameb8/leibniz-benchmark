package child_processes.count_pi;

class CalcPi {
    private static final int WARMUP_N = 2000;
    private static final int WARMUP_CALLS = 10;

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

        long startTime = System.nanoTime();
        double piApprox = calcPi(nTerms);
        long endTime = System.nanoTime();

        System.out.println((endTime - startTime) + " " + 0.0 + " " + piApprox);
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