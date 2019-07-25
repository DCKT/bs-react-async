module ReactAsync = {
  module Req = {
    type t;

    [@bs.get] external data: t => 'a = "data";
    [@bs.get] external error: t => Js.Nullable.t(Js.Exn.t) = "error";
    [@bs.get]
    external initialValue: t => Js.Nullable.t('initialValue) = "error";
    [@bs.get] external isLoading: t => bool = "isLoading";
    [@bs.get] external isPending: t => bool = "isPending";
    [@bs.get] external isRejected: t => bool = "isRejected";
    [@bs.get] external isResolved: t => bool = "isResolved";
    [@bs.get] external isSettled: t => bool = "isSettled";
    [@bs.get] external isFulfilled: t => bool = "isFulfilled";
    [@bs.get] external isInitial: t => bool = "isInitial";
  };

  module Components = {
    module Pending = {
      [@bs.module "react-async"] [@react.component]
      external make: (~state: Req.t, ~children: React.element) => React.element =
        "Pending";
    };
    module Rejected = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~children: Js.Exn.t => React.element) => React.element =
        "Rejected";
    };
    module Fulfilled = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~children: 'a => React.element) => React.element =
        "Fulfilled";
    };
  };

  [@bs.module "react-async"]
  external useAsync: ('a => Js.Promise.t('b), ~options: 'a=?, unit) => Req.t =
    "useAsync";
};