#include "part2.hh"
#include "inputparsing.hh"

std::optional<UnsignedInt> Part2::getPart2AnswersSum(std::ifstream& file) {
	std::optional<FirstPassData> firstPassAttemptResult = InputParsing::tryParseFirstPass(file);
	if (not firstPassAttemptResult.has_value()) {
		return std::nullopt;
	}
	FirstPassData& firstPassData = firstPassAttemptResult.value();

	const std::optional<std::vector<OperandStorageType>> operandsParseAttemptResult = InputParsing::tryParseVerticalOperands(file, firstPassData);
	if (not operandsParseAttemptResult.has_value()) {
		return std::nullopt;
	}
	const std::vector<OperandStorageType>& operands = operandsParseAttemptResult.value();

	UnsignedInt answerSum = 0;
	std::size_t firstHorIndexOfProblem = 0;
	for (std::size_t iProblem = 0; iProblem < firstPassData.problems_.size(); ++iProblem) {
		Problem& problem = firstPassData.problems_.at(iProblem);
		for (std::size_t iOperand = 0; iOperand < problem.widthInFile(); ++iOperand) {
			OperandStorageType operand = operands.at(firstHorIndexOfProblem + iOperand);
			problem.updateAnswer(static_cast<UnsignedInt>(operand));
		}
		answerSum += problem.answer();

		firstHorIndexOfProblem += problem.widthInFile();
	}

	return answerSum;
}
