var findJudge = function(N, trust) {
  const [trusting, trusted] = trust.reduce((result, group) => {
    result[0].push(group[0]);

    result[1][group[1]] = result[1][group[1]] === undefined ? 1 : result[1][group[1]] + 1;

    return result;
  }, [[], []])

  const mostTrustedHuman = trusted.findIndex(timesTrusted => timesTrusted === N - 1);

  const isJudgeTrusting = trusting.findIndex(human => human === mostTrustedHuman) !== -1;

  const result = isJudgeTrusting ? -1 : mostTrustedHuman;


  console.log('result', trusting, trusted, mostTrustedHuman);
  console.log('answer', result);
};

findJudge(4, [[1,3],[1,4],[2,3],[2,4],[4,3]]);