# 2018 ICPC Asia Jakarta Regional Contest - Prolem Repository

## Repository Structure

Each problem (from A to L) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug | Problem Title                     |
| ------------ | ------------ | --------------------------------- |
| A            | edit         | Edit Distance                     |
| B            | gear         | Rotating Gears                    |
| C            | thief        | Smart Thief                       |
| D            | ice          | Icy Land                          |
| E            | war          | Artilleries and Defensive Walls   |
| F            | balloon      | Popping Balloons                  |
| G            | complete     | Go Make It Complete               |
| H            | sign         | Lexical Sign Sequence             |
| I            | lie          | Lie Detector                      |
| J            | future       | Future Generation                 |
| K            | boomerang    | Boomerangs                        |
| L            | binary       | Binary String                     |

In the problem folder, there should be at least the following file/folder:

- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `alt-solution.cpp`. The second solution used to verify the outputs of the testcases
- `verifier.cpp`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.
- `tc/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `<slug>_sample_<testcase number>.in/out`, while the hidden testcases will be in the form of `<slug>_1_<testcase number>.in/out`.
- `p-<slug>.pdf`. The problem statement distributed to the contestants during the contest.

For the problem with multiple correct outputs for each input, there should be one more file in the problem folder:

- `scorer.cpp`. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will be used as the filename of the judge's output file
  - The third parameter will be used as the filename of the contestant's output file
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.

Other than the problem folder, there should also be a file named `icpc18-analysis.pdf` on the repository root. This consists the problem analysis which is also distributed to all contestants after the contest ended.

## Limitations

The following table describes the time limit for each problem, as broadcasted to all teams at the beginning of the contest:

| Problem Code | Problem Slug | Time Limit |
| ------------ | ------------ | ---------- |
| A            | edit         | 1 sec      |
| B            | gear         | 1 sec      |
| C            | thief        | 1 sec      |
| D            | ice          | 1 sec      |
| E            | war          | 1 sec      |
| F            | balloon      | 1 sec      |
| G            | complete     | 1 sec      |
| H            | sign         | 1 sec      |
| I            | lie          | 1 sec      |
| J            | future       | 1 sec      |
| K            | boomerang    | 0.5 sec    |
| L            | binary       | 0.5 sec    |

The memory limit for all problems is 256MB, as announced in the technical briefing of the contest.

## Solutions

Note that while there are only two official published solutions, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

Note that the following announcement was broadcasted to all teams during the contest:

- Problem D: Icy Land
  
```	
Correction:

"Supposed your initial position is at cell (3, 7) and your moves are east, east,
east, south, west, north, east, and east, respectively."
should be written as
"Supposed your initial position is at cell (3, 7) and your moves are west, west,
west, south, east, north, west, and west, respectively." (note the east/west
issue)

The soft copy of the problem statement in the DOMJudge has been updated, please
re-download them. Sorry for the inconvenience.
```

The soft copy of the problem statement provided in this repository is the one  distributed after the fix was made.