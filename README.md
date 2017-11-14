
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

ONLY “Standard” TAGS ARE SUPPORTED FOR THE MOMENT. ONLY `ascii` TAGS ARE
SUPPORTED FOR THE MOMENT. Full support for all tags will be here
eventually

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

    ## # A tibble: 1 x 2
    ##                        exif_key                                  exif_val
    ##                           <chr>                                     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!

Just to prove we did it:

``` r
read_exif(tf)
```

    ## # A tibble: 1 x 2
    ##                        exif_key                                  exif_val
    ##                           <chr>                                     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!

Can I have another, then?

``` r
set_exif(tf, "Exif.Image.ImageDescription", "The R logo. Duh!")
```

    ## # A tibble: 2 x 2
    ##                        exif_key                                  exif_val
    ##                           <chr>                                     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!
    ## 2   Exif.Image.ImageDescription                          The R logo. Duh!

There should be two now\!

``` r
read_exif(tf)
```

    ## # A tibble: 2 x 2
    ##                        exif_key                                  exif_val
    ##                           <chr>                                     <chr>
    ## 1 Exif.Image.ProcessingSoftware The incredibly unassuming exiv R package!
    ## 2   Exif.Image.ImageDescription                          The R logo. Duh!
