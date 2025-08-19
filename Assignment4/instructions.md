# Fall 2024 - COMP 206 - Assignment 4

This assignment is meant as practice for the long-answer question on the midterm.

You should try to solve it _on paper_ to give yourself a realistic way of practicing.

To practice for the short-answer and multiple-choice questions, check out the practice midterms
produced by your classmates in Discord.

## Problem 1: log file analysis (80 points)

In this problem, you'll analyze some more web server logs, similar to the coding-cat.log exercise
that we did in class.

The logs are in `jerrington.me.log`. This is real data from my web site, namely the last 10000
lines of the full log file at the time I created this assignment. Each line of the log represents
one request that was made to the server, generally asking it to give the content of a particular
file.

Let's break down one sample line from this dataset.

```
66.249.70.33 - - [18/Sep/2024:11:04:09 +0000] "GET /pdf/harpoon.pdf HTTP/1.1" 200 397342 "-" "Googlebot/2.1 (+http://www.google.com/bot.html)"
```

- `66.249.70.33` this set of 4 numbers is called an IP address. It identifies a node (such as a
  server or a client) on the Internet. In this log file, an IP address at the beginning of a line
  is the address of the client made the request.
- `[18/Sep/2024:11:04:09 +0000]` this is a timestamp indicating at what time the request was made.
  The specific format here is "day/month/year:hour:minute:second +timezone"
- `"GET /pdf/harpoon.pdf HTTP/1.1"` this is the first line of the request that the browser made to
  the server. It specifies that the browser would like to `GET` (download) the resource
  `/pdf/harpoon.pdf` using the `HTTP/1.1` protocol.
  Those three parts of this line are called the _HTTP method_ (or _verb_), the _path,_ and the
  _protocol_.
- The server processes the request and responds with a _status code_ that indicates whether the
  request succeeded or failed. This is similar to exit codes you're familiar with, but the numbers
  are different.
  The status code in this case was `200` which means `OK` (success). The different status codes are
  grouped according to their first digit. All status codes are exactly three digits long.
    - 1xx information: these are weird and somewhat rare
    - 2xx success: the request was processed successfully
    - 3xx redirection: these responses ask the client to make a new request to a different location
    - 4xx client error: the client made an error in the request (e.g. requesting a resource that
      does not exist causes error 404.)
    - 5xx server error: the server encountered an error while processing the request
  You can read more about HTTP response status codes [here](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)
- The log indicates how much data was sent by the server to the client, in bytes. In this case, the
  client requested a pdf file that consisted of `397342` bytes, so just shy of 400KB.
- The log indicates a _referrer,_ which is the address of the page the browser was on _before_
  it made the current request. In this case, the referrer is `"-"` meaning that either:
    - The browser suppressed the referrer information; or
    - this was the very first request.
- The final part of the log line is called the "user-agent", which identifies the kind of browser
  that made the request. In this case, it's `Googlebot`. You will find that most of the traffic to
  this site comes from bots 🥲

**Your task** is to write a script `analyze`, to be called as `./analyze COMMAND`, that
accepts various subcommands (similar to the previous assignment with worldcities.csv) to answer the
following questions about the dataset.

- `./analyze unique-ips` prints how many unique IP addresses accessed the site
- `./analyze reqs-per-day` prints how many requests per day are made on average
- `./analyze most-popular-post` determines which of the posts is the most popular. To decide this,
  count the number of `GET /posts/...` requests that give a 200 status code.
- `./analyze total-transferred` computes the total volume of data, in bytes, that was sent by the
  server, by summing the amounts given after the status codes.

If you look through the log file, you'll see that there are _many_ weird requests, which come from
hackers.

For example: `POST /cgi-bin/.%2e/.%2e/.%2e/.%2e/.%2e/.%2e/.%2e/.%2e/.%2e/.%2e/bin/sh HTTP/1.1` is
trying to run `/bin/sh` on my server by using a service called `cgi` which I fortunately am not
using on my server.

Here's another suspicious one:

```
80.82.77.202 - - [21/Sep/2024:15:51:30 +0000] "\x16\x03\x02\x01o\x01\x00\x01k\x03\x02RH\xC5\x1A#\xF7:N\xDF\xE2\xB4\x82/\xFF\x09T\x9F\xA7\xC4y\xB0h\xC6\x13\x8C\xA4\x1C=\x22\x
E1\x1A\x98 \x84\xB4,\x85\xAFn\xE3Y\xBBbhl\xFF(=':\xA9\x82\xD9o\xC8\xA2\xD7\x93\x98\xB4\xEF\x80\xE5\xB9\x90\x00(\xC0" 400 166 "-" "-"
```

This one is not even a well-formed HTTP request, which ought to look something like `GET ... HTTP/1.1`.

**Evaluation:**

Your grade is basically determined by how many of these questions your script answers.

- Answer all four: get 80/80
- Answer three: get 70/80
- Answer two: get 55/80
- Answer just one: get 40/80

## Problem 2: directory structure traversal

In class, I showed you how we can create a crude approximation of `tree` by using a recursive
bash function. In this problem, you'll use this technique to produce an approximation of the very
powerful program `find`, which as the name suggests searches for files matching given criteria.

**Your task** is to write a script `search` that shouldn't care from where it's called, to be used
in the following way:

`./search WHERE NAME` recursively searches the directory tree starting at `WHERE` and prints the
paths to _all_ the files (not directories) found whose name is `NAME`

The output should match the output of `find WHERE -name NAME -type f` except possibly for the order
of the files.

Inside your hw3 directory, you create a sample directory structure that you use to test your
script. It should go three to five levels deep, contain empty and nonempty files with different
names. The files should should have varying sizes, no more than 1kb each, and there should be no
more than 100 test files. (A dozen or two is enough to do good tests.)

**Follow-up question** create a script `total-size`. This script can expect to be called as
`./total-size WHERE NAME` and assumes that `search` is located in the same directory as it.
The script should call `./search WHERE NAME` to produce a list of matching files, get the size of
each of those files, and sum the sizes. `./total-size` should print a single number that is the
total size of all the matched files. You can get the size of a single file, in bytes,
using `wc -c FILE`.

**Evaluation:** your grade is based on completion. The scripts do not have to be perfect to get the
points.

- 15 points for completing `search`
- 5 points for completing `total-size`
