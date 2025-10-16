class CalcPi {
    public static double calcPi(int nTerms) {
        double pi = 0.0;

        for (int i = 0; i < nTerms; i++) {
            int sign = 1;

            if(i % 2 == 1)
                sign = -1;
        
            pi += sign / (2 * i + 1);
        }
        
        return 4 * pi;
    }

        public static void main(String[] args) {
        if (args.length == 0) {
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

        double piApprox = calcPi(nTerms);
        System.out.println("Pi approximation with " + nTerms + " terms: " + piApprox);
    }   
}