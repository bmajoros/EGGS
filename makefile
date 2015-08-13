C		= gcc
CC		= g++
AR		= ar -s
DEBUG		= -g
OPTIMIZE	= -O3 -finline-functions -funroll-loops
CFLAGS		= $(OPTIMIZE) -fpermissive -w
LDFLAGS		= $(OPTIMIZE) -LBOOM -lBOOM
BOOM		= BOOM
OBJ		= obj
STATIC		= -static
PHYLIB		= ../PhyLib
GSL		= BOOM/GSL
LIBS		=  -LBOOM -lBOOM -LGSL -lgsl -lm -lgslcblas

$(OBJ):
	mkdir $(OBJ)

clean:
	rm obj/*.o

#---------------------------------------------------------
$(OBJ)/GffPathFromParseGraph.o:\
		genezilla.H \
		GffPathFromParseGraph.H \
		GffPathFromParseGraph.C
	$(CC) $(CFLAGS) -o $(OBJ)/GffPathFromParseGraph.o -c \
		GffPathFromParseGraph.C
#---------------------------------------------------------
$(OBJ)/Propagator.o:\
		genezilla.H \
		Propagator.H \
		Propagator.C
	$(CC) $(CFLAGS) -o $(OBJ)/Propagator.o -c \
		Propagator.C
#---------------------------------------------------------
$(OBJ)/IsochoreTable.o:\
		IsochoreTable.H \
		IsochoreTable.C
	$(CC) $(CFLAGS) -o $(OBJ)/IsochoreTable.o -c \
		IsochoreTable.C
#---------------------------------------------------------
$(OBJ)/CodonTree.o:\
		CodonTree.H \
		CodonTree.C
	$(CC) $(CFLAGS) -o $(OBJ)/CodonTree.o -c \
		CodonTree.C
#---------------------------------------------------------
$(OBJ)/SignalPeptideSensor.o:\
		SignalPeptideSensor.H \
		SignalPeptideSensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/SignalPeptideSensor.o -c \
		SignalPeptideSensor.C
#---------------------------------------------------------
$(OBJ)/Isochore.o:\
		Isochore.H \
		Isochore.C
	$(CC) $(CFLAGS) -o $(OBJ)/Isochore.o -c \
		Isochore.C
#---------------------------------------------------------
$(OBJ)/SignalComparator.o:\
		SignalComparator.H \
		SignalComparator.C
	$(CC) $(CFLAGS) -o $(OBJ)/SignalComparator.o -c \
		SignalComparator.C
#---------------------------------------------------------
$(OBJ)/ModelBuilder.o:\
		genezilla.H \
		ModelBuilder.H \
		ModelBuilder.C
	$(CC) $(CFLAGS) -o $(OBJ)/ModelBuilder.o -c \
		ModelBuilder.C
#---------------------------------------------------------
$(OBJ)/SignalSensor.o:\
		genezilla.H \
		SignalSensor.H \
		SignalSensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/SignalSensor.o -c \
		SignalSensor.C
#---------------------------------------------------------
$(OBJ)/SignalQueue.o:\
		SignalQueue.H \
		genezilla.H \
		SignalQueue.C \
		Propagator.H \
		Signal.H
	$(CC) $(CFLAGS) -o $(OBJ)/SignalQueue.o -c \
		SignalQueue.C
#---------------------------------------------------------
$(OBJ)/MarkovChain.o:\
		genezilla.H \
		MarkovChain.H \
		MarkovChain.C
	$(CC) $(CFLAGS) -o $(OBJ)/MarkovChain.o -c \
		MarkovChain.C
#---------------------------------------------------------
$(OBJ)/ThreePeriodicIMM.o:\
		genezilla.H \
		ThreePeriodicIMM.H \
		ThreePeriodicIMM.C
	$(CC) $(CFLAGS) -o $(OBJ)/ThreePeriodicIMM.o -c \
		ThreePeriodicIMM.C
#---------------------------------------------------------
$(OBJ)/IMM.o:\
		genezilla.H \
		IMM.H \
		IMM.C
	$(CC) $(CFLAGS) -o $(OBJ)/IMM.o -c \
		IMM.C
#---------------------------------------------------------
$(OBJ)/ThreePeriodicMarkovChain.o:\
		genezilla.H \
		ThreePeriodicMarkovChain.H \
		ThreePeriodicMarkovChain.C
	$(CC) $(CFLAGS) -o $(OBJ)/ThreePeriodicMarkovChain.o -c \
		ThreePeriodicMarkovChain.C
#---------------------------------------------------------
$(OBJ)/ContentSensor.o:\
		ContentSensor.H \
		ContentSensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/ContentSensor.o -c \
		ContentSensor.C
#---------------------------------------------------------
$(OBJ)/GarbageCollector.o:\
		GarbageCollector.H \
		GarbageCollector.C
	$(CC) $(CFLAGS) -o $(OBJ)/GarbageCollector.o -c \
		GarbageCollector.C
#---------------------------------------------------------
$(OBJ)/WMM.o:\
		WMM.H \
		WMM.C
	$(CC) $(CFLAGS) -o $(OBJ)/WMM.o -c \
		WMM.C
#---------------------------------------------------------
$(OBJ)/ModelType.o:\
		ModelType.H \
		ModelType.C
	$(CC) $(CFLAGS) -o $(OBJ)/ModelType.o -c \
		ModelType.C
#---------------------------------------------------------
$(OBJ)/ScoreAnalyzer.o:\
		ScoreAnalyzer.H \
		ScoreAnalyzer.C
	$(CC) $(CFLAGS) -o $(OBJ)/ScoreAnalyzer.o -c \
		ScoreAnalyzer.C
#---------------------------------------------------------
$(OBJ)/IntronQueue.o:\
		genezilla.H \
		IntronQueue.H \
		IntronQueue.C
	$(CC) $(CFLAGS) -o $(OBJ)/IntronQueue.o -c \
		IntronQueue.C
#---------------------------------------------------------
$(OBJ)/NoncodingQueue.o:\
		genezilla.H \
		NoncodingQueue.H \
		NoncodingQueue.C
	$(CC) $(CFLAGS) -o $(OBJ)/NoncodingQueue.o -c \
		NoncodingQueue.C
#---------------------------------------------------------
$(OBJ)/DiscreteDistribution.o:\
		DiscreteDistribution.H \
		DiscreteDistribution.C
	$(CC) $(CFLAGS) -o $(OBJ)/DiscreteDistribution.o -c \
		DiscreteDistribution.C
#---------------------------------------------------------
$(OBJ)/EmpiricalDistribution.o:\
		EmpiricalDistribution.H \
		EmpiricalDistribution.C
	$(CC) $(CFLAGS) -o $(OBJ)/EmpiricalDistribution.o -c \
		EmpiricalDistribution.C
#---------------------------------------------------------
$(OBJ)/GeometricDistribution.o:\
		GeometricDistribution.H \
		GeometricDistribution.C
	$(CC) $(CFLAGS) -o $(OBJ)/GeometricDistribution.o -c \
		GeometricDistribution.C
#---------------------------------------------------------
$(OBJ)/TataCapModel.o:\
		TataCapModel.H \
		TataCapModel.C
	$(CC) $(CFLAGS) -o $(OBJ)/TataCapModel.o -c \
		TataCapModel.C
#---------------------------------------------------------
$(OBJ)/TataCapSignal.o:\
		TataCapSignal.H \
		TataCapSignal.C
	$(CC) $(CFLAGS) -o $(OBJ)/TataCapSignal.o -c \
		TataCapSignal.C
#---------------------------------------------------------
$(OBJ)/Signal.o:\
		Signal.H \
		Signal.C
	$(CC) $(CFLAGS) -o $(OBJ)/Signal.o -c \
		Signal.C
#---------------------------------------------------------
$(OBJ)/SignalTypeProperties.o:\
		SignalTypeProperties.H \
		SignalTypeProperties.C
	$(CC) $(CFLAGS) -o $(OBJ)/SignalTypeProperties.o -c \
		SignalTypeProperties.C
#---------------------------------------------------------
$(OBJ)/SignalType.o:\
		SignalType.H \
		SignalType.C
	$(CC) $(CFLAGS) -o $(OBJ)/SignalType.o -c \
		SignalType.C
#---------------------------------------------------------
$(OBJ)/ContentType.o:\
		ContentType.H \
		ContentType.C
	$(CC) $(CFLAGS) -o $(OBJ)/ContentType.o -c \
		ContentType.C
#---------------------------------------------------------
$(OBJ)/TrainingSequence.o:\
		TrainingSequence.H \
		TrainingSequence.C
	$(CC) $(CFLAGS) -o $(OBJ)/TrainingSequence.o -c \
		TrainingSequence.C
#---------------------------------------------------------
$(OBJ)/Transitions.o:\
		genezilla.H \
		Transitions.H \
		Transitions.C
	$(CC) $(CFLAGS) -o $(OBJ)/Transitions.o -c \
		Transitions.C
#---------------------------------------------------------
$(OBJ)/MarkovChainCompiler.o:\
		MarkovChainCompiler.H \
		MarkovChainCompiler.C
	$(CC) $(CFLAGS) -o $(OBJ)/MarkovChainCompiler.o -c \
		MarkovChainCompiler.C
#---------------------------------------------------------
$(OBJ)/FastMarkovChain.o:\
		genezilla.H \
		FastMarkovChain.H \
		FastMarkovChain.C
	$(CC) $(CFLAGS) -o $(OBJ)/FastMarkovChain.o -c \
		FastMarkovChain.C
#---------------------------------------------------------
$(OBJ)/Fast3PMC.o:\
		genezilla.H \
		Fast3PMC.H \
		Fast3PMC.C
	$(CC) $(CFLAGS) -o $(OBJ)/Fast3PMC.o -c \
		Fast3PMC.C
#---------------------------------------------------------
$(OBJ)/IsochoreFile.o:\
		genezilla.H \
		IsochoreFile.H \
		IsochoreFile.C
	$(CC) $(CFLAGS) -o $(OBJ)/IsochoreFile.o -c \
		IsochoreFile.C
#---------------------------------------------------------
$(OBJ)/random-genome.o:\
		genezilla.H \
		random-genome.C \
		Propagator.H \
		SignalQueue.H \
		$(BOOM)/Histogram.H \
		Signal.H
	$(CC) $(CFLAGS) -o $(OBJ)/random-genome.o -c \
		random-genome.C
#---------------------------------------------------------
$(OBJ)/sample-signal.o:\
		genezilla.H \
		sample-signal.C \
		Propagator.H \
		SignalQueue.H \
		$(BOOM)/Histogram.H \
		Signal.H
	$(CC) $(CFLAGS) -o $(OBJ)/sample-signal.o -c \
		sample-signal.C
#---------------------------------------------------------
$(OBJ)/random-TFBSs.o:\
		genezilla.H \
		random-TFBSs.C \
		Propagator.H \
		SignalQueue.H \
		$(BOOM)/Histogram.H \
		Signal.H
	$(CC) $(CFLAGS) -o $(OBJ)/random-TFBSs.o -c \
		random-TFBSs.C
#---------------------------------------------------------
$(OBJ)/GeneZilla.o:\
		$(BOOM)/Histogram.H \
		GeneZilla.H \
		GeneZilla.C
	$(CC) $(CFLAGS) -o $(OBJ)/GeneZilla.o -c \
		GeneZilla.C
#---------------------------------------------------------
$(OBJ)/TopologyLoader.o:\
		TopologyLoader.H \
		TopologyLoader.C
	$(CC) $(CFLAGS) -o $(OBJ)/TopologyLoader.o -c \
		TopologyLoader.C
#---------------------------------------------------------
$(OBJ)/Edge.o:\
		Edge.H \
		Edge.C
	$(CC) $(CFLAGS) -o $(OBJ)/Edge.o -c \
		Edge.C
#---------------------------------------------------------
$(OBJ)/EdgeFactory.o:\
		EdgeFactory.H \
		EdgeFactory.C
	$(CC) $(CFLAGS) -o $(OBJ)/EdgeFactory.o -c \
		EdgeFactory.C
#---------------------------------------------------------
$(OBJ)/WAM.o:\
		WAM.H \
		WAM.C
	$(CC) $(CFLAGS) -o $(OBJ)/WAM.o -c \
		WAM.C
#---------------------------------------------------------
$(OBJ)/BranchAcceptor.o:\
		BranchAcceptor.H \
		BranchAcceptor.C
	$(CC) $(CFLAGS) -o $(OBJ)/BranchAcceptor.o -c \
		BranchAcceptor.C
#---------------------------------------------------------
$(OBJ)/ParseGraph.o:\
		ParseGraph.H \
		ParseGraph.C \
		Edge.H \
		Signal.H
	$(CC) $(CFLAGS) -o $(OBJ)/ParseGraph.o -c \
		ParseGraph.C
#---------------------------------------------------------
$(OBJ)/WWAM.o:\
		WWAM.H \
		WWAM.C
	$(CC) $(CFLAGS) -o $(OBJ)/WWAM.o -c \
		WWAM.C
#---------------------------------------------------------
random-genome: \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/random-genome.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
	$(CC) $(LDFLAGS) -o random-genome \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/random-genome.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
		$(LDFLAGS)

#---------------------------------------------------------
$(OBJ)/BWM.o:\
		BWM.H \
		BWM.C
	$(CC) $(CFLAGS) -o $(OBJ)/BWM.o -c \
		BWM.C


#---------------------------------------------------------
$(OBJ)/MddTree.o:\
		MddTree.C \
		MddTree.H
	$(CC) $(CFLAGS) -o $(OBJ)/MddTree.o -c \
		MddTree.C
#---------------------------------------------------------
$(OBJ)/Partition.o:\
		Partition.C \
		Partition.H
	$(CC) $(CFLAGS) -o $(OBJ)/Partition.o -c \
		Partition.C
#---------------------------------------------------------
$(OBJ)/TreeNode.o:\
		TreeNode.C \
		TreeNode.H
	$(CC) $(CFLAGS) -o $(OBJ)/TreeNode.o -c \
		TreeNode.C
#---------------------------------------------------------

#---------------------------------------------------------
$(OBJ)/get-classifier-examples.o:\
		get-classifier-examples.C \
		GeneZilla.C \
		GeneZilla.H
	$(CC) $(CFLAGS) -o $(OBJ)/get-classifier-examples.o -c \
		get-classifier-examples.C
#---------------------------------------------------------
get-classifier-examples: \
		$(OBJ)/get-classifier-examples.o\
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Signal.o \
		$(OBJ)/GeneZilla.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/IsochoreFile.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IMM.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/CodonTree.o \
	$(CC) $(LDFLAGS) -o get-classifier-examples \
		$(OBJ)/get-classifier-examples.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/IMM.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/GeneZilla.o \
		$(OBJ)/Signal.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/IsochoreFile.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/SignalTypeProperties.o \
		$(STATIC)
#		$(LIBDIRS) $(LIBS)
#--------------------------------------------------------
#---------------------------------------------
$(OBJ)/generate-seq.o:\
		generate-seq.C
	$(CC) $(CFLAGS) -o $(OBJ)/generate-seq.o -c \
		generate-seq.C
#---------------------------------------------------------
generate-seq: \
		$(OBJ)/generate-seq.o
	$(CC) $(LDFLAGS) -o generate-seq \
		$(OBJ)/generate-seq.o \
		$(STATIC)
#--------------------------------------------------------
$(OBJ)/random-rate-matrix.o:\
		random-rate-matrix.C
	$(CC) $(CFLAGS) -o $(OBJ)/random-rate-matrix.o -c \
		random-rate-matrix.C
#---------------------------------------------------------
random-rate-matrix: \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/NthOrdSubstMatrix.o \
		$(OBJ)/NthOrdRateMatrix.o \
		$(OBJ)/random-rate-matrix.o
	$(CC) $(LDFLAGS) -o random-rate-matrix \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/NthOrdSubstMatrix.o \
		$(OBJ)/NthOrdRateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/random-rate-matrix.o \
		-lgsl -lm -lgslcblas $(LDFLAGS)
#--------------------------------------------------------
$(OBJ)/JukesCantor.o:\
		$(PHYLIB)/JukesCantor.C\
		$(PHYLIB)/JukesCantor.H
	$(CC) $(CFLAGS) -o $(OBJ)/JukesCantor.o -c \
		$(PHYLIB)/JukesCantor.C
#--------------------------------------------------------
$(OBJ)/IndelHistory.o:\
		$(PHYLIB)/IndelHistory.C\
		$(PHYLIB)/IndelHistory.H
	$(CC) $(CFLAGS) -o $(OBJ)/IndelHistory.o -c \
		$(PHYLIB)/IndelHistory.C
#--------------------------------------------------------
$(OBJ)/GapPattern.o:\
		$(PHYLIB)/GapPattern.C\
		$(PHYLIB)/GapPattern.H
	$(CC) $(CFLAGS) -o $(OBJ)/GapPattern.o -c \
		$(PHYLIB)/GapPattern.C
#--------------------------------------------------------
$(OBJ)/Kimura2P.o:\
		$(PHYLIB)/Kimura2P.C\
		$(PHYLIB)/Kimura2P.H
	$(CC) $(CFLAGS) -o $(OBJ)/Kimura2P.o -c \
		$(PHYLIB)/Kimura2P.C
#--------------------------------------------------------
$(OBJ)/Kimura2Param.o:\
		$(PHYLIB)/Kimura2Param.C\
		$(PHYLIB)/Kimura2Param.H
	$(CC) $(CFLAGS) -o $(OBJ)/Kimura2Param.o -c \
		$(PHYLIB)/Kimura2Param.C
#--------------------------------------------------------
$(OBJ)/FEL.o:\
		$(PHYLIB)/FEL.C\
		$(PHYLIB)/FEL.H
	$(CC) $(CFLAGS) -o $(OBJ)/FEL.o -c \
		$(PHYLIB)/FEL.C
#--------------------------------------------------------
$(OBJ)/HKY.o:\
		$(PHYLIB)/HKY.C\
		$(PHYLIB)/HKY.H
	$(CC) $(CFLAGS) -o $(OBJ)/HKY.o -c \
		$(PHYLIB)/HKY.C
#--------------------------------------------------------
$(OBJ)/REV.o:\
		$(PHYLIB)/REV.C\
		$(PHYLIB)/REV.H
	$(CC) $(CFLAGS) -o $(OBJ)/REV.o -c \
		$(PHYLIB)/REV.C
#--------------------------------------------------------
$(OBJ)/NthOrdRateMatrix.o:\
		$(PHYLIB)/NthOrdRateMatrix.C\
		$(PHYLIB)/NthOrdRateMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/NthOrdRateMatrix.o -c \
		$(PHYLIB)/NthOrdRateMatrix.C
#--------------------------------------------------------
$(OBJ)/NthOrdSubstMatrix.o:\
		$(PHYLIB)/NthOrdSubstMatrix.C\
		$(PHYLIB)/NthOrdSubstMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/NthOrdSubstMatrix.o -c \
		$(PHYLIB)/NthOrdSubstMatrix.C
#--------------------------------------------------------
$(OBJ)/RateMatrix.o:\
		$(PHYLIB)/RateMatrix.C\
		$(PHYLIB)/RateMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/RateMatrix.o -c \
		$(PHYLIB)/RateMatrix.C
#--------------------------------------------------------
$(OBJ)/SubstitutionMatrix.o:\
		$(PHYLIB)/SubstitutionMatrix.C\
		$(PHYLIB)/SubstitutionMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/SubstitutionMatrix.o -c \
		$(PHYLIB)/SubstitutionMatrix.C
#--------------------------------------------------------
$(OBJ)/RateMatrixType.o:\
		$(PHYLIB)/RateMatrixType.C\
		$(PHYLIB)/RateMatrixType.H
	$(CC) $(CFLAGS) -o $(OBJ)/RateMatrixType.o -c \
		$(PHYLIB)/RateMatrixType.C
#--------------------------------------------------------
$(OBJ)/ResidueCounter.o:\
		$(PHYLIB)/ResidueCounter.C\
		$(PHYLIB)/ResidueCounter.H
	$(CC) $(CFLAGS) -o $(OBJ)/ResidueCounter.o -c \
		$(PHYLIB)/ResidueCounter.C
#--------------------------------------------------------
$(OBJ)/Phylogeny.o:\
		$(PHYLIB)/Phylogeny.C\
		$(PHYLIB)/Phylogeny.H
	$(CC) $(CFLAGS) -o $(OBJ)/Phylogeny.o -c \
		$(PHYLIB)/Phylogeny.C
#---------------------------------------------------------
$(OBJ)/random-phylogeny.o:\
		random-phylogeny.C
	$(CC) $(CFLAGS) -o $(OBJ)/random-phylogeny.o -c \
		random-phylogeny.C
#---------------------------------------------------------
random-phylogeny: \
		$(OBJ)/IndelHistory.o \
		$(OBJ)/ResidueCounter.o \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/random-phylogeny.o
	$(CC) $(LDFLAGS) -o random-phylogeny \
		$(OBJ)/IndelHistory.o \
		$(OBJ)/ResidueCounter.o \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/random-phylogeny.o \
		-lgsl -lm -lgslcblas
#--------------------------------------------------------
$(OBJ)/evolve-seq.o:\
		evolve-seq.C
	$(CC) $(CFLAGS) -o $(OBJ)/evolve-seq.o -c \
		evolve-seq.C
#---------------------------------------------------------
evolve-seq: \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/evolve-seq.o
	$(CC) $(LDFLAGS) -o evolve-seq \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/evolve-seq.o \
		-static -lgsl -lm -lgslcblas
#--------------------------------------------------------
$(OBJ)/phy-to-newick.o:\
		phy-to-newick.C
	$(CC) $(CFLAGS) -o $(OBJ)/phy-to-newick.o -c \
		phy-to-newick.C
#---------------------------------------------------------
phy-to-newick: \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/phy-to-newick.o
	$(CC) $(LDFLAGS) -o phy-to-newick \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/phy-to-newick.o
#--------------------------------------------------------
$(OBJ)/evolve-genome.o:\
		evolve-genome.C
	$(CC) $(CFLAGS) -o $(OBJ)/evolve-genome.o -c \
		evolve-genome.C
#---------------------------------------------------------
evolve-genome: \
		$(OBJ)/NmerRateMatrix.o \
		$(OBJ)/NmerSubstMatrix.o \
		$(OBJ)/PeriodicRateMatrix.o \
		$(OBJ)/PeriodicSubstMatrix.o \
		$(OBJ)/NthOrdRateMatrix.o \
		$(OBJ)/NthOrdSubstMatrix.o \
		$(OBJ)/GapPattern.o \
		$(OBJ)/IndelHistory.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/WMM.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/Signal.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/Genome.o \
		$(OBJ)/GenomeFeature.o \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/IMM.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/evolve-genome.o
	$(CC) $(LDFLAGS) -o evolve-genome \
		$(OBJ)/NmerRateMatrix.o \
		$(OBJ)/NmerSubstMatrix.o \
		$(OBJ)/PeriodicRateMatrix.o \
		$(OBJ)/PeriodicSubstMatrix.o \
		$(OBJ)/NthOrdRateMatrix.o \
		$(OBJ)/NthOrdSubstMatrix.o \
		$(OBJ)/GapPattern.o \
		$(OBJ)/IndelHistory.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/IMM.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/Partition.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/WMM.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/Signal.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Genome.o \
		$(OBJ)/GenomeFeature.o \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/evolve-genome.o \
		-lgsl -lm -lgslcblas $(LDFLAGS)
#--------------------------------------------------------
$(OBJ)/GenomeFeature.o:\
		GenomeFeature.C\
		GenomeFeature.H
	$(CC) $(CFLAGS) -o $(OBJ)/GenomeFeature.o -c \
		GenomeFeature.C
#---------------------------------------------------------
$(OBJ)/Genome.o:\
		Genome.C\
		Genome.H
	$(CC) $(CFLAGS) -o $(OBJ)/Genome.o -c \
		Genome.C
#---------------------------------------------------------
random-TFBSs: \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/random-TFBSs.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
	$(CC) $(LDFLAGS) -o random-TFBSs \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/random-TFBSs.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
		$(STATIC)
		$(LIBDIRS) $(LIBS)
#---------------------------------------------------------

#--------------------------------------------------------
$(OBJ)/orf-lengths.o:\
		orf-lengths.C
	$(CC) $(CFLAGS) -o $(OBJ)/orf-lengths.o -c \
		orf-lengths.C
#---------------------------------------------------------
orf-lengths: \
		$(OBJ)/orf-lengths.o
	$(CC) $(LDFLAGS) -o orf-lengths \
		$(OBJ)/orf-lengths.o \
		$(STATIC)
#---------------------------------------------------------
sample-signal: \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/sample-signal.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
	$(CC) $(LDFLAGS) -o sample-signal \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/sample-signal.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
		$(STATIC)
		$(LIBDIRS) $(LIBS)
#---------------------------------------------
#--------------------------------------------------------
$(OBJ)/get-subst-matrices.o:\
		get-subst-matrices.C
	$(CC) $(CFLAGS) -o $(OBJ)/get-subst-matrices.o -c \
		get-subst-matrices.C
#---------------------------------------------------------
get-subst-matrices: \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/get-subst-matrices.o
	$(CC) $(LDFLAGS) -o get-subst-matrices \
		$(OBJ)/Phylogeny.o \
		$(OBJ)/JukesCantor.o \
		$(OBJ)/Kimura2Param.o \
		$(OBJ)/HKY.o \
		$(OBJ)/FEL.o \
		$(OBJ)/REV.o \
		$(OBJ)/RateMatrixType.o \
		$(OBJ)/RateMatrix.o \
		$(OBJ)/SubstitutionMatrix.o \
		$(OBJ)/get-subst-matrices.o \
		-lgsl -lm -lgslcblas
#--------------------------------------------------------
#--------------------------------------------------------
$(OBJ)/chunk-maf.o:\
		chunk-maf.C
	$(CC) $(CFLAGS) -o $(OBJ)/chunk-maf.o -c \
		chunk-maf.C
#---------------------------------------------------------
chunk-maf: \
		$(OBJ)/chunk-maf.o
	$(CC) $(LDFLAGS) -o chunk-maf \
		$(OBJ)/chunk-maf.o \
		-lgsl -lm -lgslcblas
#--------------------------------------------------------

#--------------------------------------------------------
$(OBJ)/split-maf-by-gff.o:\
		split-maf-by-gff.C
	$(CC) $(CFLAGS) -o $(OBJ)/split-maf-by-gff.o -c \
		split-maf-by-gff.C
#---------------------------------------------------------
split-maf-by-gff: \
		$(OBJ)/split-maf-by-gff.o
	$(CC) $(LDFLAGS) -o split-maf-by-gff \
		$(OBJ)/split-maf-by-gff.o \
		-lgsl -lm -lgslcblas
#--------------------------------------------------------


#--------------------------------------------------------
$(OBJ)/matrix-power.o:\
		matrix-power.C
	$(CC) $(CFLAGS) -o $(OBJ)/matrix-power.o -c \
		matrix-power.C
#---------------------------------------------------------
matrix-power: \
		$(OBJ)/matrix-power.o
	$(CC) $(LDFLAGS) -o matrix-power \
		$(OBJ)/matrix-power.o \
		-lgsl -lm -lgslcblas
#---------------------------------------------

#--------------------------------------------------------
$(OBJ)/subset-maf-tracks.o:\
		subset-maf-tracks.C
	$(CC) $(CFLAGS) -o $(OBJ)/subset-maf-tracks.o -c \
		subset-maf-tracks.C
#---------------------------------------------------------
subset-maf-tracks: \
		$(OBJ)/subset-maf-tracks.o
	$(CC) $(LDFLAGS) -o subset-maf-tracks \
		$(OBJ)/subset-maf-tracks.o \
		-lgsl -lm -lgslcblas $(LDFLAGS)
#--------------------------------------------------------
#--------------------------------------------------------
$(OBJ)/PeriodicRateMatrix.o:\
		$(PHYLIB)/PeriodicRateMatrix.C\
		$(PHYLIB)/PeriodicRateMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/PeriodicRateMatrix.o -c \
		$(PHYLIB)/PeriodicRateMatrix.C
#---------------------------------------------------------

#--------------------------------------------------------
$(OBJ)/PeriodicSubstMatrix.o:\
		$(PHYLIB)/PeriodicSubstMatrix.C\
		$(PHYLIB)/PeriodicSubstMatrix.H
	$(CC) $(CFLAGS) -o $(OBJ)/PeriodicSubstMatrix.o -c \
		$(PHYLIB)/PeriodicSubstMatrix.C
#---------------------------------------------------------


#--------------------------------------------------------
$(OBJ)/DegenerateDnaMatch.o:\
		$(PHYLIB)/DegenerateDnaMatch.C\
		$(PHYLIB)/DegenerateDnaMatch.H
	$(CC) $(CFLAGS) -o $(OBJ)/DegenerateDnaMatch.o -c \
		$(PHYLIB)/DegenerateDnaMatch.C
#---------------------------------------------------------
#---------------------------------------------------------
$(OBJ)/NmerRateMatrix.o:\
		$(PHYLIB)/NmerRateMatrix.H \
		$(PHYLIB)/NmerRateMatrix.C
	$(CC) $(CFLAGS) -o $(OBJ)/NmerRateMatrix.o -c \
		$(PHYLIB)/NmerRateMatrix.C
#---------------------------------------------------------
$(OBJ)/NmerSubstMatrix.o:\
		$(PHYLIB)/NmerSubstMatrix.H \
		$(PHYLIB)/NmerSubstMatrix.C
	$(CC) $(CFLAGS) -o $(OBJ)/NmerSubstMatrix.o -c \
		$(PHYLIB)/NmerSubstMatrix.C

#--------------------------------------------------------
$(OBJ)/get-WMM-cutoff.o:\
		get-WMM-cutoff.C
	$(CC) $(CFLAGS) -o $(OBJ)/get-WMM-cutoff.o -c \
		get-WMM-cutoff.C
#---------------------------------------------------------
get-WMM-cutoff: \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
		$(OBJ)/get-WMM-cutoff.o
	$(CC) $(LDFLAGS) -o get-WMM-cutoff \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o \
		$(OBJ)/get-WMM-cutoff.o \
		$(LIBS)
#---------------------------------------------

#--------------------------------------------------------
$(OBJ)/convert-from-JASPAR.o:\
		convert-from-JASPAR.C
	$(CC) $(CFLAGS) -o $(OBJ)/convert-from-JASPAR.o -c \
		convert-from-JASPAR.C
#---------------------------------------------------------
convert-from-JASPAR: \
		$(OBJ)/convert-from-JASPAR.o
	$(CC) $(LDFLAGS) -o convert-from-JASPAR \
		$(OBJ)/convert-from-JASPAR.o \
		$(LIBS)
#--------------------------------------------------------
$(OBJ)/apply-signal-sensor.o:\
		apply-signal-sensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/apply-signal-sensor.o -c \
		apply-signal-sensor.C
#---------------------------------------------------------
apply-signal-sensor: \
		$(OBJ)/apply-signal-sensor.o
	$(CC) -o apply-signal-sensor \
		$(OBJ)/apply-signal-sensor.o \
		$(OPTIMIZE) -L. -lEGGS -LBOOM -lBOOM -LGSL -lgsl -lm -lgslcblas
#--------------------------------------------------------
$(OBJ)/train-signal-sensor.o:\
		train-signal-sensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/train-signal-sensor.o -c \
		train-signal-sensor.C
#---------------------------------------------------------
train-signal-sensor: \
		$(OBJ)/train-signal-sensor.o
	$(CC) -o train-signal-sensor \
		$(OBJ)/train-signal-sensor.o \
		$(OPTIMIZE) -L. -lEGGS -LBOOM -lBOOM -L$(GSL) -lgsl -lcblas
#--------------------------------------------------------
$(OBJ)/train-content-sensor.o:\
		train-content-sensor.C
	$(CC) $(CFLAGS) -o $(OBJ)/train-content-sensor.o -c \
		train-content-sensor.C
#---------------------------------------------------------
train-content-sensor: \
		$(OBJ)/train-content-sensor.o
	$(CC) -o train-content-sensor \
		$(OBJ)/train-content-sensor.o \
		$(OPTIMIZE) -L. -lEGGS -LBOOM -lBOOM
#---------------------------------------------
libEGGS.a: 	$(OBJ) \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/ModelType.o \
		$(OBJ)/GeneZilla.o
	$(AR) -r libEGGS.a \
		$(OBJ)/SignalPeptideSensor.o \
		$(OBJ)/ModelType.o \
		$(OBJ)/CodonTree.o \
		$(OBJ)/SignalComparator.o \
		$(OBJ)/Isochore.o \
		$(OBJ)/IsochoreTable.o \
		$(OBJ)/BranchAcceptor.o \
		$(OBJ)/ParseGraph.o \
		$(OBJ)/GffPathFromParseGraph.o \
		$(OBJ)/ThreePeriodicIMM.o \
		$(OBJ)/IMM.o \
		$(OBJ)/EdgeFactory.o \
		$(OBJ)/MddTree.o \
		$(OBJ)/Partition.o \
		$(OBJ)/TreeNode.o \
		$(OBJ)/GarbageCollector.o \
		$(OBJ)/Edge.o \
		$(OBJ)/TrainingSequence.o \
		$(OBJ)/TopologyLoader.o \
		$(OBJ)/WAM.o \
		$(OBJ)/WWAM.o \
		$(OBJ)/TataCapModel.o \
		$(OBJ)/TataCapSignal.o \
		$(OBJ)/MarkovChainCompiler.o \
		$(OBJ)/Fast3PMC.o \
		$(OBJ)/FastMarkovChain.o \
		$(OBJ)/ThreePeriodicMarkovChain.o \
		$(OBJ)/DiscreteDistribution.o \
		$(OBJ)/Transitions.o \
		$(OBJ)/EmpiricalDistribution.o \
		$(OBJ)/GeometricDistribution.o \
		$(OBJ)/NoncodingQueue.o \
		$(OBJ)/IntronQueue.o \
		$(OBJ)/SignalType.o \
		$(OBJ)/ContentType.o \
		$(OBJ)/ModelBuilder.o \
		$(OBJ)/ScoreAnalyzer.o \
		$(OBJ)/ContentSensor.o \
		$(OBJ)/MarkovChain.o \
		$(OBJ)/WMM.o \
		$(OBJ)/SignalQueue.o \
		$(OBJ)/SignalSensor.o \
		$(OBJ)/Propagator.o \
		$(OBJ)/Signal.o \
		$(OBJ)/SignalTypeProperties.o \
		$(OBJ)/GeneZilla.o
