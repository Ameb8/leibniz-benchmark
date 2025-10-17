const WARMUP_RUNS = 3
const WARMUP_N = 10000;


function calcPi(nTerms) {
    let pi = 0.0;

    for(let i = 0; i < nTerms; i++) {
        let sign = 1;

        if(i % 2 == 1)
            sign = -1;
    
        pi += sign / (2.0 * i + 1);
    }
    
    return 4 * pi;
}

function runBenchmark(nTerms) {
    for(let i =0; i < WARMUP_RUNS; i++)
        calcPi(WARMUP_N);

    // Start benchmark timings
    const wallStart = Date.now();
    const cpuStart = performance.now();

    const pi = calcPi(nTerms); // Run benchmark

    // End benchmark timing
    const wallEnd = Date.now();
    const cpuEnd = performance.now();

    // Calculate Results in seconds
    const wallTimeSec = (wallEnd - wallStart) / 1000;
    const cpuTimeSec = (cpuEnd - cpuStart) / 1000;

    // Output results
    console.log(`${wallTimeSec} ${cpuTimeSec} ${pi}`)
}

function main() {
    const args = process.argv.slice(2);  // ignore 'node' and program name in CL args
    
    if(args.length < 1) { // No nTerms provided
        console.error('Please provide the number of terms as a command-line argument.');
        process.exit(1);
    }

    const nTerms = Number(args[0]); // Parse nTerms to numerical value

    // nTerms arg is not valid integer
    if (isNaN(nTerms) || nTerms <= 0 || !Number.isInteger(nTerms)) {
        console.error(`Invalid number format: ${args[0]}`);
        process.exit(1);
    }

    runBenchmark(nTerms); // Run the benchmark
}

// Run main if this script is executed directly
if (require.main === module) {
    main();
}
