
# exiv

## Description

Read and Write ‘Exif’ Image Tags

### README FIRST\!\!\!

This package shld work on macOS and Linux systems that have the
[`exiv2`](http://www.exiv2.org/) package installed.

  - macOS: `brew install exiv2`
  - Ubuntu/Debian `sudo apt-get install exiv2`

For the time being, it needs to be easily findable. It’ll be more robust
when the pkg is out of Alpha status.

ONLY “Standard” TAGS ARE SUPPORTED FOR THE MOMENT.

Value types currently supported:

  - `ascii`
  - `long`
  - `short`
  - `rational`
  - `srational`
  - `comment`

## What’s Inside The Tin

The following functions are implemented:

  - `read_exif`: Retrieve Exif Data From An Image
  - `set_exif`: Set Exif tag data on an image file
  - `exif_tags`: Return a data frame of all possible Exif tags

## Installation

``` r
devtools::install_github("hrbrmstr/exiv")
```

## Usage

``` r
library(exiv)
library(tidyverse)

# current verison
packageVersion("exiv")
```

    ## [1] '0.1.0'

### Tags, you say?

We got your tags, *right here*:

``` r
exif_tags(filter_type="ascii")
```

    ## # A tibble: 49 x 4
    ##                              key  type
    ##                            <chr> <chr>
    ##  1 Exif.Image.ProcessingSoftware ascii
    ##  2       Exif.Image.DocumentName ascii
    ##  3   Exif.Image.ImageDescription ascii
    ##  4               Exif.Image.Make ascii
    ##  5              Exif.Image.Model ascii
    ##  6           Exif.Image.Software ascii
    ##  7           Exif.Image.DateTime ascii
    ##  8             Exif.Image.Artist ascii
    ##  9       Exif.Image.HostComputer ascii
    ## 10           Exif.Image.InkNames ascii
    ## # ... with 39 more rows, and 2 more variables: description <chr>, rname <chr>

### Read exif data

This shld be an empty data frame:

``` r
r_logo <- system.file("extdata", "Rlogo.png", package="exiv")

read_exif(r_logo)
```

    ## # A tibble: 0 x 0

Let’s move it and add some ASCII metadata\!

``` r
tf <- tempfile(fileext=".png")
file.copy(r_logo, tf)
```

    ## [1] TRUE

``` r
set_exif(tf, "Exif.Image.ProcessingSoftware", "The incredibly unassuming exiv R package!")
```

    ## # A tibble: 1 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii

Just to prove we did it:

``` r
read_exif(tf)
```

    ## # A tibble: 1 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii

Can I have another, then?

``` r
set_exif(tf, "Exif.Image.ImageDescription", "The R logo. Duh!")
```

    ## # A tibble: 2 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii

There should be two now\!

``` r
read_exif(tf)
```

    ## # A tibble: 2 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii

Some numerics:

``` r
set_exif(tf, "Exif.Image.ImageWidth", 1000)
```

    ## # A tibble: 3 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2         Exif.Image.ImageWidth                                      1000     SLong
    ## 3   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii

``` r
set_exif(tf, "Exif.Image.RatingPercent", 30)
```

    ## # A tibble: 4 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2         Exif.Image.ImageWidth                                      1000     SLong
    ## 3   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii
    ## 4      Exif.Image.RatingPercent                                        30     Short

``` r
set_exif(tf, "Exif.Image.YResolution", c(-2, 3))
```

    ## # A tibble: 5 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2         Exif.Image.ImageWidth                                      1000     SLong
    ## 3   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii
    ## 4        Exif.Image.YResolution                                      -2/3 SRational
    ## 5      Exif.Image.RatingPercent                                        30     Short

``` r
set_exif(tf, "Exif.Photo.DateTimeOriginal", as.character(Sys.time()))
```

    ## # A tibble: 7 x 3
    ##                        exif_key                                  exif_val exif_type
    ##                           <chr>                                     <chr>     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!     Ascii
    ## 2         Exif.Image.ImageWidth                                      1000     SLong
    ## 3   Exif.Image.ImageDescription                          The R logo. Duh!     Ascii
    ## 4        Exif.Image.YResolution                                      -2/3 SRational
    ## 5      Exif.Image.RatingPercent                                        30     Short
    ## 6            Exif.Image.ExifTag                                       154      Long
    ## 7   Exif.Photo.DateTimeOriginal                       2017-11-14 22:29:46     Ascii
