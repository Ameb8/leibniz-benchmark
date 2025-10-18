package main

import (
	"fmt"
	"os"
	"strconv"
	"syscall"
	"time"
)

func calcPi(nTerms int) float64 {
	pi := 0.0

	for i := 0; i < nTerms; i++ {
		sign := 1

		if i%2 == 1 {
			sign = -1
		}

		pi += float64(sign) / (2.0*float64(i) + 1.0)
	}

	return 4.0 * pi
}

func getCPUTime() time.Duration {
	var ru syscall.Rusage
	syscall.Getrusage(syscall.RUSAGE_SELF, &ru)
	user := time.Duration(ru.Utime.Sec)*time.Second + time.Duration(ru.Utime.Usec)*time.Microsecond
	sys := time.Duration(ru.Stime.Sec)*time.Second + time.Duration(ru.Stime.Usec)*time.Microsecond
	return user + sys
}

func main() {
	// Basic CLI argument parsing
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "Error: missing nTerms argument")
		os.Exit(1)
	}

	nTerms, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error: nTerms must be an integer")
		os.Exit(1)
	}

	// Optional warm-up
	_ = calcPi(100000)

	// Start timing
	startWall := time.Now()
	startCPU := getCPUTime()

	// Run once
	result := calcPi(nTerms)

	// End timing
	elapsedWall := time.Since(startWall)
	elapsedCPU := getCPUTime() - startCPU

	// Output results
	fmt.Printf("%.6f %.6f %.10f\n", elapsedWall.Seconds(), elapsedCPU.Seconds(), result)
}
