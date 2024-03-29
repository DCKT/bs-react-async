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
    [@bs.send] external reload: (t, unit) => unit = "reload";
  };

  module Components = {
    module IfInitial = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~persist: bool=?, ~children: React.element) =>
        React.element =
        "IfInitial";
    };
    module IfPending = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~persist: bool=?, ~children: React.element) =>
        React.element =
        "IfPending";
    };
    module IfRejected = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (
          ~state: Req.t,
          ~persist: bool=?,
          ~children: Js.Exn.t => React.element
        ) =>
        React.element =
        "IfRejected";
    };
    module IfFulfilled = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~persist: bool=?, ~children: 'a => React.element) =>
        React.element =
        "IfFulfilled";
    };
    module IfSettled = {
      [@bs.module "react-async"] [@react.component]
      external make:
        (~state: Req.t, ~persist: bool=?, ~children: 'a => React.element) =>
        React.element =
        "IfSettled";
    };
  };

  [@bs.deriving abstract]
  type options('a, 'b, 'i, 't) = {
    [@bs.optional]
    initialValue: 'i,
    [@bs.optional]
    watch: 'a,
    [@bs.optional]
    watchFn: 'a => 'b,
    [@bs.optional]
    debugLabel: string,
    [@bs.optional]
    promise: Js.Promise.t('t),
    [@bs.optional]
    onResolve: 'a => unit,
    [@bs.optional]
    onReject: Js.Exn.t => unit,
    [@bs.optional]
    onCancel: unit => unit,
  };

  [@bs.module "react-async"]
  external useAsyncWithOptions:
    ('a => Js.Promise.t('b), ~options: options('c, 'd, 'e, 'f)=?, unit) =>
    Req.t =
    "useAsync";

  [@bs.module "react-async"] external _useAsync: 'a => Req.t = "useAsync";

  let useAsync = (~promiseFn, ~params=?, ()) =>
    _useAsync(
      Js.Obj.assign(
        {"promiseFn": promiseFn},
        params->Belt.Option.getWithDefault(Js.Obj.empty()),
      ),
    );
};