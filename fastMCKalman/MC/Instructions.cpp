gSystem->AddIncludePath("-I\"$fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/\"")
      gSystem->Load("$fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/AliExternalTrackParam.so");
   .L $fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.cxx+g
    .L $fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulationTest.C+g