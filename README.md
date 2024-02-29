# March-Madness-Bracket-Simulator

This is a program that I wrote that uses historical NCAA Men's Basketball Tournament data to predict the outcome of a bracket.

The idea is not to predict the most likely outcome of the tournament, but instead to generate reasonable and varied brackets that are free from individual bias.
Each year myself and a group of my friends all make several brackets each and see if anyone can beat the bot's average score in the ESPN contest. So far the bot is undefeated.

The logic is simple. It loads in data for every tournament game played since 1985, and looks at historical seeding matchups. For example, maybe a 2 seed has played a 4 seed 100 times
and the 2 seed has won 85 of those games. Then the simulator would simply award the win to the 2 seed 85% of the time.

There are some additional restrictions. The bracket gets thrown out if there are any seeds 12 or higher in the final four (this has never happened), and it also throws out any brackets
that have any seed higher than 4 winning it all. This has happened 3 times, but eliminating these brackets increases the bots average score in general. Also any bracket that predicts a
champion not belonging to the major 6 conferences gets thrown out. This is also imprecise but in general it improves the average score.

As the years go by and I run out of silly and imprecise options for making it better, I may eventually have to do some actual statistical analysis, but that sounds like more work
than this whimsical project was ever supposed to be about!
