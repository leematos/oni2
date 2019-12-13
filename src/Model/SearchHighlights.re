/*
 * SearchHighlights.re
 *
 * Per-buffer highlight info
 */

open EditorCoreTypes;
open Oni_Core;

type matchingPair = {
  startPos: Location.t,
  endPos: Location.t,
};

type highlights = {
  matchingPair: option(matchingPair),
  highlightRanges: IntMap.t(list(Range.t)),
};

let default: highlights = {matchingPair: None, highlightRanges: IntMap.empty};

type t = IntMap.t(highlights);

let create: unit => t = () => IntMap.empty;

let highlightRangesToMap = (ranges: list(Range.t)) => {
  List.fold_left(
    (prev, cur) =>
      Range.(
        IntMap.update(
          Index.toZeroBased(cur.start.line),
          v =>
            switch (v) {
            | None => Some([cur])
            | Some(v) => Some([cur, ...v])
            },
          prev,
        )
      ),
    IntMap.empty,
    ranges,
  );
};

let reduce = (action: Actions.t, state: t) => {
  switch (action) {
  | SearchSetMatchingPair(bid, startPos, endPos) =>
    IntMap.update(
      bid,
      oldHighlights =>
        switch (oldHighlights) {
        | None => Some({...default, matchingPair: Some({startPos, endPos})})
        | Some(v) => Some({...v, matchingPair: Some({startPos, endPos})})
        },
      state,
    )
  | SearchSetHighlights(bid, ranges) =>
    let highlightRanges = highlightRangesToMap(ranges);
    IntMap.update(
      bid,
      oldHighlights =>
        switch (oldHighlights) {
        | None => Some({...default, highlightRanges})
        | Some(v) => Some({...v, highlightRanges})
        },
      state,
    );
  | SearchClearHighlights(bid) => IntMap.update(bid, _ => None, state)
  | SearchClearMatchingPair(bid) =>
    IntMap.update(
      bid,
      oldHighlights =>
        switch (oldHighlights) {
        | None => None
        | Some(v) => Some({...v, matchingPair: None})
        },
      state,
    )
  | _ => state
  };
};